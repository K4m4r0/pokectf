#!/usr/bin/env python3
"""
Bridge Flag Patcher for pokeemerald-expansion (mGBA/RetroArch saves)

Important: This version might only work with .sav files from mGBA Emulator, based on a save where the flag
was set in-game (ground truth). In that build:

- FLAG_FLAG8_BRIDGE_SET has ID 0x4EE
- Flags live in SaveBlock1 sector ID 2
- The correct byte for flag 0x4EE is at sector2.data[0x38D], bit 0x40

So we patch:
  sectorId=2, dataOffset=0x38D, OR with 0x40
and then recompute the sector checksum exactly like save.c CalculateChecksum().

Works for .sav, .srm, and any extension. Preserves trailing bytes beyond 0x20000.
"""

from __future__ import annotations

import os
import struct
import tkinter as tk
from tkinter import ttk, filedialog, messagebox
from pathlib import Path
from typing import Optional, Tuple, List

# --- Save format constants ---
SECTOR_SIZE = 0x1000
SECTOR_DATA_SIZE = 0x0F80
NUM_SECTORS_PER_SLOT = 14
SLOT0_BASE = 0x00000
SLOT1_BASE = 0x0E000
MIN_SAVE_BYTES = 0x20000

OFF_ID = 0x0FF4
OFF_CHECKSUM = 0x0FF6
OFF_SIGNATURE = 0x0FF8
SECTOR_SIGNATURE = 0x08012025  # bytes: 25 20 01 08

# --- Challenge constants (CURRENT build) ---
TARGET_SECTOR_ID = 2
TARGET_OFF_IN_SECTOR = 0x38D     # sector2.data[0x38D]
TARGET_MASK = 0x40              # bit for flag 0x4EE

# For checksum size of SaveBlock1 chunk #1 (sector id 2): full 0xF80 in your build
CHECKSUM_SIZE_FOR_SECTOR2 = SECTOR_DATA_SIZE


def u16_le(buf: bytes, off: int) -> int:
    return struct.unpack_from("<H", buf, off)[0]


def u32_le(buf: bytes, off: int) -> int:
    return struct.unpack_from("<I", buf, off)[0]


def w16_le(buf: bytearray, off: int, v: int) -> None:
    struct.pack_into("<H", buf, off, v & 0xFFFF)


def calculate_checksum_like_rom(data: bytes, size: int) -> int:
    """
    Matches save.c CalculateChecksum(void *data, u16 size):
      sum u32 words for (size/4) iterations, then return (sum + (sum >> 16)) as u16.
    """
    acc = 0
    for i in range(size // 4):
        acc = (acc + struct.unpack_from("<I", data, i * 4)[0]) & 0xFFFFFFFF
    return (acc + (acc >> 16)) & 0xFFFF


def slot_present(buf: bytes, slot_base: int) -> bool:
    return len(buf) >= slot_base + NUM_SECTORS_PER_SLOT * SECTOR_SIZE


def find_sector_base(buf: bytes, slot_base: int, logical_id: int) -> Optional[int]:
    for phys in range(NUM_SECTORS_PER_SLOT):
        sec_base = slot_base + phys * SECTOR_SIZE
        if sec_base + SECTOR_SIZE > len(buf):
            continue
        if u32_le(buf, sec_base + OFF_SIGNATURE) != SECTOR_SIGNATURE:
            continue
        if u16_le(buf, sec_base + OFF_ID) == logical_id:
            return sec_base
    return None


def atomic_write(path: Path, data: bytes) -> None:
    tmp = path.with_name(path.name + ".tmp")
    with open(tmp, "wb") as f:
        f.write(data)
        f.flush()
        try:
            os.fsync(f.fileno())
        except OSError:
            pass
    os.replace(tmp, path)


def read_status(buf: bytes, slot_base: int) -> Tuple[Optional[bool], str]:
    if not slot_present(buf, slot_base):
        return None, "slot not present"
    sec = find_sector_base(buf, slot_base, TARGET_SECTOR_ID)
    if sec is None:
        return None, f"sectorId={TARGET_SECTOR_ID} not found"
    b = buf[sec + TARGET_OFF_IN_SECTOR]
    return bool(b & TARGET_MASK), f"sectorId={TARGET_SECTOR_ID} data[0x{TARGET_OFF_IN_SECTOR:X}] byte=0x{b:02X} mask=0x{TARGET_MASK:02X}"


def patch_slot(buf: bytearray, slot_base: int) -> Tuple[bool, str]:
    if not slot_present(buf, slot_base):
        return False, f"slotBase=0x{slot_base:X}: slot not present"
    sec = find_sector_base(buf, slot_base, TARGET_SECTOR_ID)
    if sec is None:
        return False, f"slotBase=0x{slot_base:X}: sectorId={TARGET_SECTOR_ID} not found"

    abs_target = sec + TARGET_OFF_IN_SECTOR
    old = buf[abs_target]
    buf[abs_target] = old | TARGET_MASK
    new = buf[abs_target]
    status = "already set" if (old & TARGET_MASK) else "set now"

    # Fix checksum for this sector (sectorId=2)
    sector_data = bytes(buf[sec:sec + SECTOR_DATA_SIZE])
    chk = calculate_checksum_like_rom(sector_data, CHECKSUM_SIZE_FOR_SECTOR2)
    w16_le(buf, sec + OFF_CHECKSUM, chk)

    return True, (
        f"slotBase=0x{slot_base:X}: {status}; sectorId=2 data[0x{TARGET_OFF_IN_SECTOR:X}] "
        f"{old:02X}->{new:02X}; checksum=0x{chk:04X}"
    )


def patch_file(in_path: Path, out_path: Path, inplace: bool, make_backup: bool) -> List[str]:
    raw = in_path.read_bytes()
    if len(raw) < MIN_SAVE_BYTES:
        raise RuntimeError(f"File too small: {len(raw)} bytes. Need at least {MIN_SAVE_BYTES}.")

    head = bytearray(raw[:MIN_SAVE_BYTES])
    tail = raw[MIN_SAVE_BYTES:]

    logs: List[str] = []
    logs.append(f"Input:  {in_path}")
    logs.append(f"Size:   {len(raw)} bytes (0x{len(raw):X})")
    if tail:
        logs.append(f"Note: trailing bytes kept unchanged: {len(tail)}")

    b0, i0 = read_status(head, SLOT0_BASE)
    b1, i1 = read_status(head, SLOT1_BASE) if slot_present(head, SLOT1_BASE) else (None, "slot not present")
    logs.append(f"Before Slot0: {b0} ({i0})")
    logs.append(f"Before Slot1: {b1} ({i1})")

    ok0, m0 = patch_slot(head, SLOT0_BASE)
    ok1, m1 = (False, "slot not present")
    if slot_present(head, SLOT1_BASE):
        ok1, m1 = patch_slot(head, SLOT1_BASE)

    logs.append(("OK   " if ok0 else "SKIP ") + m0)
    logs.append(("OK   " if ok1 else "SKIP ") + m1)

    a0, j0 = read_status(head, SLOT0_BASE)
    a1, j1 = read_status(head, SLOT1_BASE) if slot_present(head, SLOT1_BASE) else (None, "slot not present")
    logs.append(f"After  Slot0: {a0} ({j0})")
    logs.append(f"After  Slot1: {a1} ({j1})")

    out_bytes = bytes(head) + tail

    if inplace:
        if make_backup:
            bak = Path(str(in_path) + ".bak")
            if not bak.exists():
                bak.write_bytes(raw)
                logs.append(f"Backup: {bak}")
            else:
                logs.append(f"Backup exists: {bak} (not overwritten)")
        out_path = in_path

    atomic_write(out_path, out_bytes)
    logs.append(f"Output: {out_path}")
    return logs


class App(ttk.Frame):
    def __init__(self, master: tk.Tk) -> None:
        super().__init__(master)
        self.master = master

        self.selected_file = tk.StringVar(value="")
        self.inplace = tk.BooleanVar(value=True)
        self.make_backup = tk.BooleanVar(value=True)

        self.status_slot0 = tk.StringVar(value="Slot0: (no file)")
        self.status_slot1 = tk.StringVar(value="Slot1: (no file)")

        self._build_ui()

    def _build_ui(self) -> None:
        self.master.title("Bridge Flag Patcher (current build) - Flag 0x4EE")
        self.master.geometry("940x560")
        self.pack(fill="both", expand=True, padx=12, pady=12)

        file_frame = ttk.LabelFrame(self, text="1) Select save file (.sav / .srm / any)")
        file_frame.pack(fill="x")
        ttk.Entry(file_frame, textvariable=self.selected_file).pack(side="left", fill="x", expand=True, padx=(10, 8), pady=10)
        ttk.Button(file_frame, text="Browse...", command=self.on_browse).pack(side="left", padx=(0, 10), pady=10)

        st_frame = ttk.LabelFrame(self, text="2) Status (sectorId=2, data[0x38D] bit 0x40)")
        st_frame.pack(fill="x", pady=(12, 0))
        ttk.Label(st_frame, textvariable=self.status_slot0).pack(anchor="w", padx=10, pady=(8, 2))
        ttk.Label(st_frame, textvariable=self.status_slot1).pack(anchor="w", padx=10, pady=(0, 8))

        opt = ttk.LabelFrame(self, text="3) Options")
        opt.pack(fill="x", pady=(12, 0))
        row = ttk.Frame(opt); row.pack(fill="x", padx=10, pady=10)
        ttk.Checkbutton(row, text="Patch in place (recommended)", variable=self.inplace).pack(side="left")
        ttk.Checkbutton(row, text="Create .bak backup", variable=self.make_backup).pack(side="left", padx=(18, 0))
        ttk.Button(row, text="Re-check status", command=self.on_verify).pack(side="right")

        action = ttk.Frame(self); action.pack(fill="x", pady=(12, 0))
        self.btn_patch = ttk.Button(action, text="Patch Bridge Flag", command=self.on_patch_inplace)
        self.btn_patch.pack(side="left")
        self.btn_copy = ttk.Button(action, text="Patch to copy...", command=self.on_patch_copy)
        self.btn_copy.pack(side="left", padx=(10, 0))
        self.pb = ttk.Progressbar(action, mode="indeterminate")
        self.pb.pack(side="left", fill="x", expand=True, padx=12)
        self.status = ttk.Label(action, text="Ready.")
        self.status.pack(side="left")

        logf = ttk.LabelFrame(self, text="4) Log")
        logf.pack(fill="both", expand=True, pady=(12, 0))
        self.text = tk.Text(logf, height=16, wrap="word")
        self.text.pack(side="left", fill="both", expand=True, padx=(10, 0), pady=10)
        scroll = ttk.Scrollbar(logf, command=self.text.yview)
        scroll.pack(side="left", fill="y", padx=(0, 10), pady=10)
        self.text.configure(yscrollcommand=scroll.set)

    def log(self, line: str) -> None:
        self.text.insert("end", line + "\n")
        self.text.see("end")

    def set_status(self, s: str) -> None:
        self.status.config(text=s)
        self.master.update_idletasks()

    def _get_path(self) -> Optional[Path]:
        p = self.selected_file.get().strip()
        return Path(p) if p else None

    def on_browse(self) -> None:
        path = filedialog.askopenfilename(
            title="Select save file",
            filetypes=[("Save files", "*.sav *.srm *.dat *.bin *.flash"), ("All files", "*.*")]
        )
        if path:
            self.selected_file.set(path)
            self.log(f"Selected: {path}")
            self.on_verify()

    def on_verify(self) -> None:
        p = self._get_path()
        if not p or not p.is_file():
            return
        raw = p.read_bytes()
        head = raw[:MIN_SAVE_BYTES] if len(raw) >= MIN_SAVE_BYTES else raw
        s0, i0 = read_status(head, SLOT0_BASE)
        s1, i1 = read_status(head, SLOT1_BASE) if slot_present(head, SLOT1_BASE) else (None, "slot not present")
        self.status_slot0.set(f"Slot0: {s0} ({i0})")
        self.status_slot1.set(f"Slot1: {s1} ({i1})")

    def _run_patch(self, inplace: bool, out_path: Optional[Path]) -> None:
        in_path = self._get_path()
        if not in_path or not in_path.is_file():
            messagebox.showerror("No file", "Please select the emulator save file first.")
            return

        if not inplace and out_path is None:
            messagebox.showerror("No output", "Choose an output filename.")
            return

        self.btn_patch.config(state="disabled")
        self.btn_copy.config(state="disabled")
        self.pb.start(12)
        self.set_status("Patching...")
        self.log("---- PATCH START ----")

        try:
            if inplace:
                logs = patch_file(in_path, in_path, True, self.make_backup.get())
            else:
                logs = patch_file(in_path, out_path, False, False)  # type: ignore[arg-type]
            for l in logs:
                self.log(l)
            self.log("---- PATCH DONE ----")
            self.set_status("Success")
            self.on_verify()
            messagebox.showinfo("Patched", "Patched successfully.\n\nClose the emulator while patching.")
        except Exception as e:
            self.set_status("Failed")
            self.log(f"ERROR: {e}")
            messagebox.showerror("Patch failed", str(e))
        finally:
            self.pb.stop()
            self.btn_patch.config(state="normal")
            self.btn_copy.config(state="normal")

    def on_patch_inplace(self) -> None:
        self._run_patch(True, None)

    def on_patch_copy(self) -> None:
        in_path = self._get_path()
        if not in_path:
            messagebox.showerror("No file", "Select a save file first.")
            return
        default_name = in_path.with_name(f"{in_path.stem}.patched{in_path.suffix}")
        out_str = filedialog.asksaveasfilename(
            title="Save patched copy as...",
            initialfile=default_name.name,
            initialdir=str(default_name.parent),
            defaultextension=in_path.suffix,
            filetypes=[("Save files", "*.sav *.srm *.dat *.bin *.flash"), ("All files", "*.*")]
        )
        if not out_str:
            return
        self._run_patch(False, Path(out_str))


def main() -> int:
    root = tk.Tk()
    try:
        style = ttk.Style()
        if "clam" in style.theme_names():
            style.theme_use("clam")
    except Exception:
        pass
    App(root)
    root.mainloop()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
