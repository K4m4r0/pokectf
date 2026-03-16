#!/usr/bin/env python3

# -*- coding: utf-8 -*-
import re
import tkinter as tk
from tkinter import ttk
from tkinter.scrolledtext import ScrolledText


MAX_DEFAULT = 34
LINES_PER_BOX_DEFAULT = 2

# Eingabe-Modi für vorhandene Steuerzeichen
MODE_IGNORE_ALL = "Neu umbrechen (ignoriere \\n und \\p)"
MODE_KEEP_P = "\\p behalten, \\n neu umbrechen"
MODE_KEEP_ALL = "\\n und \\p beibehalten"

# Akzeptiert .string / .text / .script tolerant
_STRING_DIRECTIVE_RE = re.compile(
    r"""
    ^\s*                          # leading whitespace
    \.(?:string|text|script)\s+   # directive
    "                             # opening quote
    (                             # capture content
      (?:\\.|[^"\\])*             # escaped char OR not a quote/backslash
    )
    "                             # closing quote
    """,
    re.VERBOSE | re.MULTILINE,
)

# Split für Steuerzeichen
_CONTROL_SPLIT_RE = re.compile(r"(\\n|\\p|\$)")


def _extract_text_from_directives(raw: str) -> str | None:
    """Wenn raw .string/.text/.script enthält: Inhalte extrahieren, sonst None."""
    matches = list(_STRING_DIRECTIVE_RE.finditer(raw))
    if not matches:
        return None

    parts = []
    for m in matches:
        s = m.group(1)
        # nur \" wieder zu " machen; \n und \p als Steuersequenzen behalten
        s = s.replace(r"\"", '"')
        parts.append(s)

    return "".join(parts)


def _normalize_ws_preserve_controls(text: str) -> str:
    """
    Whitespace normalisieren, ohne \n/\p/$ zu zerstören.
    """
    text = text.replace("\t", " ")
    # Platzhalter setzen
    text = text.replace(r"\p", "<<P>>").replace(r"\n", "<<N>>").replace("$", "<<D>>")
    text = re.sub(r"\s+", " ", text).strip()
    # Platzhalter zurück
    text = text.replace("<<P>>", r"\p").replace("<<N>>", r"\n").replace("<<D>>", "$")
    return text


def _tokenize_with_controls(text: str):
    """
    Tokens:
      - ("WORD", "abc")
      - ("NL", None) für \n
      - ("PAGE", None) für \p
      - ("END", None) für $
    """
    chunks = _CONTROL_SPLIT_RE.split(text)
    for ch in chunks:
        if not ch:
            continue
        if ch == r"\n":
            yield ("NL", None)
        elif ch == r"\p":
            yield ("PAGE", None)
        elif ch == "$":
            yield ("END", None)
            return
        else:
            for w in re.findall(r"\S+", ch):
                yield ("WORD", w)


def _wrap_tokens(tokens, max_chars: int):
    """
    Wrap in items:
      - ("LINE", "text")
      - ("PAGEBREAK", None)
    """
    items = []
    current = ""

    def flush_line():
        nonlocal current
        if current:
            items.append(("LINE", current))
            current = ""

    for ttype, value in tokens:
        if ttype == "END":
            flush_line()
            break

        if ttype == "PAGE":
            flush_line()
            items.append(("PAGEBREAK", None))
            continue

        if ttype == "NL":
            flush_line()
            continue

        # WORD
        w = value
        if not current:
            current = w
        else:
            candidate = current + " " + w
            if len(candidate) <= max_chars:
                current = candidate
            else:
                items.append(("LINE", current))
                current = w

    flush_line()

    # trailing pagebreaks entfernen
    while items and items[-1][0] == "PAGEBREAK":
        items.pop()

    return items


def _format_items_to_strings(items, indent: str, lines_per_box: int):
    """
    Convert LINE/PAGEBREAK items into .string lines with \n, \p and final $.
    """
    lines = []
    for kind, val in items:
        if kind == "PAGEBREAK":
            if lines:
                lines[-1]["force_page_end"] = True
            continue
        if kind == "LINE":
            lines.append({"text": val, "force_page_end": False})

    if not lines:
        return ""

    out = []
    line_in_box = 0  # 0..lines_per_box-1

    for i, line in enumerate(lines):
        is_last = (i == len(lines) - 1)
        text = line["text"].replace('"', r'\"')  # quotes escapen

        if is_last:
            suffix = "$"
        else:
            if line["force_page_end"] or (line_in_box == lines_per_box - 1):
                suffix = r"\p"
                line_in_box = 0
            else:
                suffix = r"\n"
                line_in_box += 1

        out.append(f'{indent}.string "{text}{suffix}"')

    return "\n".join(out)


def reformat_poke_text(
    raw_input: str,
    max_chars: int = MAX_DEFAULT,
    lines_per_box: int = LINES_PER_BOX_DEFAULT,
    indent: str = "\t",
    normalize_whitespace: bool = True,
    input_control_mode: str = MODE_IGNORE_ALL,
):
    """
    Accepts either plain text or existing .string blocks.
    input_control_mode:
      - IGNORE_ALL: entfernt vorhandene \n/\p/$ und bricht komplett neu um
      - KEEP_P:     behält \p als harte Pagebreaks, ignoriert \n (reflow innerhalb jeder Page)
      - KEEP_ALL:   respektiert \n und \p exakt
    """
    raw = raw_input.replace("\r\n", "\n").replace("\r", "\n").strip()
    if not raw:
        return ""

    extracted = _extract_text_from_directives(raw)
    if extracted is not None:
        text = extracted
    else:
        # Plain text: leere Zeilen => Absatz, zwischen Absätzen \p
        parts = re.split(r"\n\s*\n+", raw)
        cleaned = []
        for p in parts:
            p = re.sub(r"\s*\n\s*", " ", p.strip())
            p = re.sub(r"\s+", " ", p).strip()
            if p:
                cleaned.append(p)
        text = r"\p".join(cleaned)

    # Steuerzeichen-Modus anwenden (wichtig: vor dem Tokenizing)
    if input_control_mode == MODE_IGNORE_ALL:
        text = text.replace(r"\n", " ").replace(r"\p", " ").replace("$", " ")
    elif input_control_mode == MODE_KEEP_P:
        text = text.replace(r"\n", " ").replace("$", " ")
        # \p bleibt erhalten
    elif input_control_mode == MODE_KEEP_ALL:
        # alles bleibt, inkl. $
        pass
    else:
        # Fallback: wie IGNORE_ALL
        text = text.replace(r"\n", " ").replace(r"\p", " ").replace("$", " ")

    if normalize_whitespace:
        text = _normalize_ws_preserve_controls(text)

    tokens = list(_tokenize_with_controls(text))
    items = _wrap_tokens(tokens, max_chars=max_chars)
    return _format_items_to_strings(items, indent=indent, lines_per_box=lines_per_box)


# --------- GUI ---------

class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("pokeemerald-advance .string Formatter")
        self.geometry("1000x720")

        self.columnconfigure(0, weight=1)
        self.rowconfigure(3, weight=1)
        self.rowconfigure(6, weight=1)

        top = ttk.Frame(self, padding=10)
        top.grid(row=0, column=0, sticky="ew")
        top.columnconfigure(30, weight=1)

        ttk.Label(top, text="Max Zeichen pro Zeile:").grid(row=0, column=0, sticky="w")
        self.max_chars = tk.IntVar(value=MAX_DEFAULT)
        ttk.Spinbox(top, from_=1, to=200, textvariable=self.max_chars, width=6).grid(row=0, column=1, padx=(6, 14))

        ttk.Label(top, text="Zeilen pro Textbox (bis \\p):").grid(row=0, column=2, sticky="w")
        self.lines_per_box = tk.IntVar(value=LINES_PER_BOX_DEFAULT)
        ttk.Spinbox(top, from_=1, to=10, textvariable=self.lines_per_box, width=6).grid(row=0, column=3, padx=(6, 14))

        ttk.Label(top, text="Einrückung:").grid(row=0, column=4, sticky="w")
        self.indent_choice = tk.StringVar(value="Tab")
        ttk.Combobox(
            top,
            textvariable=self.indent_choice,
            values=["Tab", "4 Spaces", "Keine"],
            width=10,
            state="readonly",
        ).grid(row=0, column=5, padx=(6, 14))

        self.normalize_ws = tk.BooleanVar(value=True)
        ttk.Checkbutton(top, text="Whitespace normalisieren", variable=self.normalize_ws)\
            .grid(row=0, column=6, padx=(0, 14), sticky="w")

        # NEU: Auswahl wie mit \n/\p aus Input umzugehen ist
        ttk.Label(top, text="Eingabe-Steuercodes:").grid(row=0, column=7, sticky="w")
        self.ctrl_mode = tk.StringVar(value=MODE_KEEP_P)  # Default: \p behalten, \n reflow
        ttk.Combobox(
            top,
            textvariable=self.ctrl_mode,
            values=[MODE_IGNORE_ALL, MODE_KEEP_P, MODE_KEEP_ALL],
            width=34,
            state="readonly",
        ).grid(row=0, column=8, sticky="w")

        btns = ttk.Frame(self, padding=(10, 0, 10, 10))
        btns.grid(row=1, column=0, sticky="ew")
        btns.columnconfigure(3, weight=1)

        ttk.Button(btns, text="Formatieren", command=self.on_format).grid(row=0, column=0, padx=(0, 8))
        ttk.Button(btns, text="Output kopieren", command=self.copy_output).grid(row=0, column=1, padx=(0, 8))
        ttk.Button(btns, text="Alles leeren", command=self.clear_all).grid(row=0, column=2)

        self.status = tk.StringVar(value="Bereit.")
        ttk.Label(btns, textvariable=self.status).grid(row=0, column=3, sticky="e")

        ttk.Label(
            self,
            text="Input (normaler Text ODER vorhandene .string \"...\\n\" / \\p / $ Blöcke):",
            padding=(10, 0, 10, 0),
        ).grid(row=2, column=0, sticky="w")

        self.input_box = ScrolledText(self, height=12, wrap="word")
        self.input_box.grid(row=3, column=0, sticky="nsew", padx=10)

        ttk.Label(self, text="Output (kopierbar):", padding=(10, 10, 10, 0)).grid(row=5, column=0, sticky="w")
        self.output_box = ScrolledText(self, height=14, wrap="none")
        self.output_box.grid(row=6, column=0, sticky="nsew", padx=10, pady=(0, 10))

        # Beispiel (zeigt gut den Nutzen von KEEP_P)
        self.input_box.insert(
            "1.0",
            '.string "These are Blackhansa\'s servers, with \\n"\n'
            '.string "all their secrets. If only I had something\\p"\n'
            '.string "I could connect to intercept the data traffic.$"\n'
        )

    def _indent(self) -> str:
        v = self.indent_choice.get()
        if v == "Tab":
            return "\t"
        if v == "4 Spaces":
            return "    "
        return ""

    def on_format(self):
        raw = self.input_box.get("1.0", "end").rstrip("\n")
        if not raw.strip():
            self.output_box.delete("1.0", "end")
            self.status.set("Kein Input.")
            return

        out = reformat_poke_text(
            raw_input=raw,
            max_chars=int(self.max_chars.get()),
            lines_per_box=int(self.lines_per_box.get()),
            indent=self._indent(),
            normalize_whitespace=bool(self.normalize_ws.get()),
            input_control_mode=self.ctrl_mode.get(),
        )

        self.output_box.delete("1.0", "end")
        self.output_box.insert("1.0", out)

        n = out.count("\n") + (1 if out.strip() else 0)
        self.status.set(f"Fertig. {n} .string-Zeilen.")

    def copy_output(self):
        out = self.output_box.get("1.0", "end").rstrip("\n")
        if not out.strip():
            self.status.set("Kein Output zum Kopieren.")
            return
        self.clipboard_clear()
        self.clipboard_append(out)
        self.status.set("Output kopiert.")

    def clear_all(self):
        self.input_box.delete("1.0", "end")
        self.output_box.delete("1.0", "end")
        self.status.set("Geleert.")


if __name__ == "__main__":
    App().mainloop()
