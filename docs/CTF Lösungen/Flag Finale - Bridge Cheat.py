#!/usr/bin/env python3
"""
Bridgeroom Bridge Flag Patcher (GUI)
- Works with .sav, .srm, or any extension (you choose the file)
- Patches FLAG_FLAG8_BRIDGE_SET (0x4EE) for your build
- Fixes checksum exactly like your save.c
- Gives visual feedback (flag status + logs)
"""

from __future__ import annotations

import struct
import tkinter as tk
from tkinter import ttk, filedialog, messagebox
from pathlib import Path
from typing import Optional, Tuple, List


# -----------------------------
# Save-format constants (from your project)
# -----------------------------
SECTOR_SIZE = 0x1000
SECTOR_DATA_SIZE = 3968  # 0xF80
NUM_SECTORS_PER_SLOT = 14

SLOT0_BASE = 0x00000  # sectors 0-13
SLOT1_BASE = 0x0E000  # sectors 14-27

OFF_ID        = 0x0FF4
OFF_CHECKSUM  = 0x0FF6
OFF_SIGNATURE = 0x0FF8

SECTOR_SIGNATURE = 0x08012025  # bytes: 25 20 01 08 (little-endian)

# Your measured values
SB1_SIZE = 0x3D98
SB1_FLAGS_OFF = 0x1348

FLAGS_SECTOR_ID = 1 + (SB1_FLAGS_OFF // SECTOR_DATA_SIZE)  # = 2
FLAGS_OFFSET_IN_SECTOR = SB1_FLAGS_OFF % SECTOR_DATA_SIZE  # = 0x3C8

DEFAULT_FLAG_ID = 0x4EE  # FLAG_FLAG8_BRIDGE_SET


# -----------------------------
# Binary helpers
# -----------------------------
def read_u16_le(buf: bytes, off: int) -> int:
    return struct.unpack_from("<H", buf, off)[0]


def read_u32_le(buf: bytes, off: int) -> int:
    return struct.unpack_from("<I", buf, off)[0]


def write_u16_le(buf: bytearray, off: int, v: int) -> None:
    struct.pack_into("<H", buf, off, v & 0xFFFF)


def parse_int(s: str) -> int:
    s = s.strip().lower()
    return int(s, 16) if s.startswith("0x") else int(s, 10)


def calculate_checksum_like_rom(data: bytes, size: int) -> int:
    """
    Matches your save.c CalculateChecksum(void *data, u16 size):
      sum u32 words for (size/4) iterations, return (sum + (sum>>16)) as u16
    """
    words = size // 4
    acc = 0
    for i in range(words):
        acc = (acc + struct.unpack_from("<I", data, i * 4)[0]) & 0xFFFFFFFF
    return (acc + (acc >> 16)) & 0xFFFF


def find_sector_by_logical_id(buf: bytes, slot_base: int, logical_id: int) -> Optional[int]:
    """
    Scan the 14 physical sectors in a slot; find sector with correct signature + footer id.
    Returns absolute file offset of the sector base.
    """
    for phys in range(NUM_SECTORS_PER_SLOT):
        sec_base = slot_base + phys * SECTOR_SIZE
        if sec_base + OFF_SIGNATURE + 4 > len(buf):
            return None
        sig = read_u32_le(buf, sec_base + OFF_SIGNATURE)
        if sig != SECTOR_SIGNATURE:
            continue
        sid = read_u16_le(buf, sec_base + OFF_ID)
        if sid == logical_id:
            return sec_base
    return None


def slot_present(buf: bytes, slot_base: int) -> bool:
    return len(buf) >= slot_base + NUM_SECTORS_PER_SLOT * SECTOR_SIZE


def get_flag_status_in_slot(buf: bytes, slot_base: int, flag_id: int) -> Tuple[Optional[bool], str]:
    """
    Returns (True/False) if we can read it, else (None) with reason.
    """
    if not slot_present(buf, slot_base):
        return None, "slot not present in file size"

    sec_base = find_sector_by_logical_id(buf, slot_base, FLAGS_SECTOR_ID)
    if sec_base is None:
        return None, f"sectorId={FLAGS_SECTOR_ID} not found (signature mismatch/empty)"

    byte_index = flag_id // 8
    bit_index = flag_id % 8
    mask = 1 << bit_index

    target_off = FLAGS_OFFSET_IN_SECTOR + byte_index
    if target_off >= SECTOR_DATA_SIZE:
        return None, "computed target offset out of sector data"

    b = buf[sec_base + target_off]
    return (b & mask) != 0, f"sectorId={FLAGS_SECTOR_ID}, data[0x{target_off:X}], mask=0x{mask:02X}"


def patch_slot(buf: bytearray, slot_base: int, flag_id: int) -> Tuple[bool, str]:
    """
    Patch one slot: set bit and update checksum for sectorId=2.
    """
    if not slot_present(buf, slot_base):
        return False, f"slotBase=0x{slot_base:X}: slot not present in file size."

    sec_base = find_sector_by_logical_id(buf, slot_base, FLAGS_SECTOR_ID)
    if sec_base is None:
        return False, f"slotBase=0x{slot_base:X}: sectorId={FLAGS_SECTOR_ID} not found (empty or invalid signature)."

    byte_index = flag_id // 8
    bit_index = flag_id % 8
    mask = 1 << bit_index

    target_off = FLAGS_OFFSET_IN_SECTOR + byte_index  # for 0x4EE => 0x465
    abs_target = sec_base + target_off

    old = buf[abs_target]
    already_set = (old & mask) != 0
    new = old | mask
    buf[abs_target] = new

    # For sector ID 2 in your build, this SB1 chunk is full 0xF80 bytes.
    chk_size = SECTOR_DATA_SIZE
    sector_data = bytes(buf[sec_base: sec_base + SECTOR_DATA_SIZE])
    checksum = calculate_checksum_like_rom(sector_data, chk_size)
    write_u16_le(buf, sec_base + OFF_CHECKSUM, checksum)

    status = "already set" if already_set else "set now"
    return True, (
        f"slotBase=0x{slot_base:X}: {status} | sectorId={FLAGS_SECTOR_ID} "
        f"data[0x{target_off:X}] {old:02X}->{new:02X} | checksum=0x{checksum:04X}"
    )


def patch_save_file(in_path: Path, out_path: Path, flag_id: int, inplace: bool, make_backup: bool) -> List[str]:
    raw = in_path.read_bytes()
    buf = bytearray(raw)

    logs: List[str] = []
    logs.append(f"Input:  {in_path}")
    logs.append(f"Size:   {len(raw)} bytes (0x{len(raw):X})")
    logs.append(f"Flag:   0x{flag_id:X}")
    logs.append(f"Target: sectorId={FLAGS_SECTOR_ID}, flagsStart=0x{FLAGS_OFFSET_IN_SECTOR:X}, "
                f"flagByteIndex=0x{flag_id//8:X} => sector.data[0x{FLAGS_OFFSET_IN_SECTOR + (flag_id//8):X}]")

    # Status before
    st0, info0 = get_flag_status_in_slot(raw, SLOT0_BASE, flag_id)
    st1, info1 = get_flag_status_in_slot(raw, SLOT1_BASE, flag_id)
    logs.append(f"Before Slot0: {st0} ({info0})")
    logs.append(f"Before Slot1: {st1} ({info1})")

    ok0, msg0 = patch_slot(buf, SLOT0_BASE, flag_id)
    logs.append(("OK   " if ok0 else "SKIP ") + msg0)

    ok1, msg1 = patch_slot(buf, SLOT1_BASE, flag_id)
    logs.append(("OK   " if ok1 else "SKIP ") + msg1)

    if not ok0 and not ok1:
        raise RuntimeError("Could not patch any slot (sectorId=2 not found with valid signature). "
                           "Most common cause: you selected the wrong save file.")

    # Backup + write
    if inplace:
        if make_backup:
            bak = in_path.with_suffix(in_path.suffix + ".bak")
            if not bak.exists():
                bak.write_bytes(raw)
                logs.append(f"Backup: {bak}")
            else:
                logs.append(f"Backup exists: {bak} (not overwritten)")
        out_path = in_path

    out_path.write_bytes(buf)
    logs.append(f"Output: {out_path}")

    # Status after (read from new bytes)
    new_bytes = bytes(buf)
    st0a, info0a = get_flag_status_in_slot(new_bytes, SLOT0_BASE, flag_id)
    st1a, info1a = get_flag_status_in_slot(new_bytes, SLOT1_BASE, flag_id)
    logs.append(f"After  Slot0: {st0a} ({info0a})")
    logs.append(f"After  Slot1: {st1a} ({info1a})")

    return logs


# -----------------------------
# Tkinter GUI
# -----------------------------
class App(ttk.Frame):
    def __init__(self, master: tk.Tk) -> None:
        super().__init__(master)
        self.master = master

        self.selected_file = tk.StringVar(value="")
        self.flag_hex = tk.StringVar(value="0x4EE")

        # Make inplace the safe default so emulator definitely uses it
        self.inplace = tk.BooleanVar(value=True)
        self.make_backup = tk.BooleanVar(value=True)

        self.status_slot0 = tk.StringVar(value="Slot0: (no file)")
        self.status_slot1 = tk.StringVar(value="Slot1: (no file)")

        self._build_ui()

    def _build_ui(self) -> None:
        self.master.title("Bridgeroom Bridge Flag Patcher (works with .sav/.srm)")
        self.master.geometry("900x560")
        self.pack(fill="both", expand=True, padx=12, pady=12)

        # File picker
        file_frame = ttk.LabelFrame(self, text="1) Select save file (.sav / .srm / any)")
        file_frame.pack(fill="x")

        ttk.Entry(file_frame, textvariable=self.selected_file).pack(
            side="left", fill="x", expand=True, padx=(10, 8), pady=10
        )
        ttk.Button(file_frame, text="Browse…", command=self.on_browse).pack(
            side="left", padx=(0, 10), pady=10
        )

        # Status readout
        st_frame = ttk.LabelFrame(self, text="Current flag status (read-only)")
        st_frame.pack(fill="x", pady=(12, 0))

        ttk.Label(st_frame, textvariable=self.status_slot0).pack(anchor="w", padx=10, pady=(8, 2))
        ttk.Label(st_frame, textvariable=self.status_slot1).pack(anchor="w", padx=10, pady=(0, 8))

        # Options
        opt_frame = ttk.LabelFrame(self, text="2) Options")
        opt_frame.pack(fill="x", pady=(12, 0))

        row1 = ttk.Frame(opt_frame)
        row1.pack(fill="x", padx=10, pady=(10, 6))
        ttk.Label(row1, text="Flag ID:").pack(side="left")
        ttk.Entry(row1, textvariable=self.flag_hex, width=12).pack(side="left", padx=(6, 18))
        ttk.Label(row1, text="(default 0x4EE = bridge)").pack(side="left")

        row2 = ttk.Frame(opt_frame)
        row2.pack(fill="x", padx=10, pady=(0, 10))
        ttk.Checkbutton(row2, text="Patch in place (recommended)", variable=self.inplace).pack(side="left")
        ttk.Checkbutton(row2, text="Create .bak backup", variable=self.make_backup).pack(side="left", padx=(18, 0))
        ttk.Button(row2, text="Re-check status", command=self.on_verify).pack(side="right")

        # Actions
        action_frame = ttk.Frame(self)
        action_frame.pack(fill="x", pady=(12, 0))

        self.btn_patch = ttk.Button(action_frame, text="Patch now (spawn bridge)", command=self.on_patch)
        self.btn_patch.pack(side="left")

        self.btn_saveas = ttk.Button(action_frame, text="Patch to copy…", command=self.on_patch_to_copy)
        self.btn_saveas.pack(side="left", padx=(10, 0))

        self.pb = ttk.Progressbar(action_frame, mode="indeterminate")
        self.pb.pack(side="left", fill="x", expand=True, padx=12)

        self.status = ttk.Label(action_frame, text="Ready.")
        self.status.pack(side="left")

        # Log
        details = ttk.LabelFrame(self, text="3) Log / Feedback")
        details.pack(fill="both", expand=True, pady=(12, 0))

        self.text = tk.Text(details, height=18, wrap="word")
        self.text.pack(side="left", fill="both", expand=True, padx=(10, 0), pady=10)

        scroll = ttk.Scrollbar(details, command=self.text.yview)
        scroll.pack(side="left", fill="y", padx=(0, 10), pady=10)
        self.text.configure(yscrollcommand=scroll.set)

        # Footer constants
        footer = ttk.LabelFrame(self, text="Build constants")
        footer.pack(fill="x", pady=(12, 0))
        const_text = (
            f"SB1 size=0x{SB1_SIZE:X} | flags off=0x{SB1_FLAGS_OFF:X} | "
            f"flags sectorId={FLAGS_SECTOR_ID} | flags start=0x{FLAGS_OFFSET_IN_SECTOR:X} | "
            f"0x4EE => sector.data[0x465] mask 0x40"
        )
        ttk.Label(footer, text=const_text).pack(anchor="w", padx=10, pady=8)

    def log(self, line: str) -> None:
        self.text.insert("end", line + "\n")
        self.text.see("end")

    def set_status(self, text: str) -> None:
        self.status.config(text=text)
        self.master.update_idletasks()

    def _get_selected_path(self) -> Optional[Path]:
        p = self.selected_file.get().strip()
        if not p:
            return None
        return Path(p)

    def _read_flag_status(self, path: Path, flag_id: int) -> None:
        try:
            raw = path.read_bytes()
            st0, info0 = get_flag_status_in_slot(raw, SLOT0_BASE, flag_id)
            st1, info1 = get_flag_status_in_slot(raw, SLOT1_BASE, flag_id)
            self.status_slot0.set(f"Slot0: {st0} ({info0})")
            self.status_slot1.set(f"Slot1: {st1} ({info1})")
        except Exception as e:
            self.status_slot0.set(f"Slot0: error ({e})")
            self.status_slot1.set(f"Slot1: error ({e})")

    def on_browse(self) -> None:
        path = filedialog.askopenfilename(
            title="Select your save file",
            filetypes=[
                ("Save files", "*.sav *.srm *.bin *.flash *.dat"),
                ("All files", "*.*"),
            ],
        )
        if path:
            self.selected_file.set(path)
            self.log(f"Selected: {path}")
            # auto-verify
            self.on_verify()

    def on_verify(self) -> None:
        path = self._get_selected_path()
        if not path or not path.is_file():
            return
        try:
            flag_id = parse_int(self.flag_hex.get())
        except Exception:
            flag_id = DEFAULT_FLAG_ID
        self._read_flag_status(path, flag_id)

    def _run_patch(self, inplace: bool, out_path: Optional[Path]) -> None:
        in_path = self._get_selected_path()
        if not in_path or not in_path.is_file():
            messagebox.showerror("No file", "Please select your actual emulator save file first (.srm/.sav).")
            return

        try:
            flag_id = parse_int(self.flag_hex.get())
        except Exception:
            messagebox.showerror("Invalid flag", "Flag ID must be hex (0x...) or decimal.")
            return

        if not inplace:
            assert out_path is not None

        # UI busy
        self.btn_patch.config(state="disabled")
        self.btn_saveas.config(state="disabled")
        self.pb.start(12)
        self.set_status("Patching…")
        self.log("---- PATCH START ----")

        try:
            if inplace:
                # write back to same file
                logs = patch_save_file(in_path, in_path, flag_id, inplace=True, make_backup=self.make_backup.get())
            else:
                logs = patch_save_file(in_path, out_path, flag_id, inplace=False, make_backup=False)

            for l in logs:
                self.log(l)

            self.log("---- PATCH DONE ----")
            self.set_status("Success ✅")

            self._read_flag_status((in_path if inplace else out_path), flag_id)

            messagebox.showinfo(
                "Patched!",
                "Patched successfully.\n\n"
                "If the bridge still doesn't appear:\n"
                "1) Make sure you patched the SAME file the emulator uses (.srm is common).\n"
                "2) Restart emulator / reload save.\n"
                "3) Ensure you load into Bridgeroom (map script runs on load)."
            )

        except Exception as e:
            self.set_status("Failed ❌")
            self.log(f"ERROR: {e}")
            messagebox.showerror("Patch failed", str(e))

        finally:
            self.pb.stop()
            self.btn_patch.config(state="normal")
            self.btn_saveas.config(state="normal")

    def on_patch(self) -> None:
        # in place
        self._run_patch(inplace=True, out_path=None)

    def on_patch_to_copy(self) -> None:
        in_path = self._get_selected_path()
        if not in_path:
            messagebox.showerror("No file", "Select a save file first.")
            return

        # default: preserve extension and use NAME.patched.ext
        default_name = in_path.with_name(f"{in_path.stem}.patched{in_path.suffix}")

        out_str = filedialog.asksaveasfilename(
            title="Save patched copy as…",
            initialfile=default_name.name,
            initialdir=str(default_name.parent),
            defaultextension=in_path.suffix,
            filetypes=[
                ("Save files", "*.sav *.srm *.bin *.flash *.dat"),
                ("All files", "*.*"),
            ],
        )
        if not out_str:
            return

        self._run_patch(inplace=False, out_path=Path(out_str))


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
