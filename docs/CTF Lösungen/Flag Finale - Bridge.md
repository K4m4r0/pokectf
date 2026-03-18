# CTF Bridge Challenge — Full Solution (Bridgeroom)

Goal: Make the bridge appear in **Bridgeroom** by setting the save flag  
`FLAG_FLAG8_BRIDGE_SET` with ID **0x4EE**.

Important: This solution might only work with a .sav file made by the mGBA Emulator. Here the flag is **not** located at the “vanilla” offset you might expect from `offsetof(SaveBlock1, flags)`. The save layout includes an additional shifting/indirection, so you must use the **verified on-save location** below (or use the provided patcher).

Also note: The bridge tiles are maybe only **materialized when you interact with the sign** in Bridgeroom.

Workflow: **edit save → fix checksum → load save → read sign → bridge appears**.

---

## What you need

- Your emulator save file (`.sav` or `.srm`) (**make a backup**)
- A hex editor (HxD / ImHex / 010 Editor / etc.)
- A way to compute a 16-bit checksum (a small script/tool is easiest)
- (Recommended) The provided GUI patcher: `bridge_patcher_current_build_gui.py`

---

## Step 0 — Make a clean “before” save

1. Stand in **Bridgeroom** where the missing bridge should be.
2. Save the game normally (no save states).
3. Close the emulator completely (so it flushes the save file).
4. Copy the save file and keep a backup (e.g. `save_before_bridge.sav`).

---

## Step 1 — Understand what a valid Gen-III save slot looks like

A Gen-III save has **two save slots** (Slot 0 and Slot 1). Each slot contains **14 sectors**, each sector is **0x1000 bytes**.

Within each 0x1000-byte sector:
- Sector data: `0x0000 .. 0x0F7F` (3968 bytes = **0xF80**)
- Footer at the end:
  - `+0x0FF4` = Sector **ID** (u16, little-endian)
  - `+0x0FF6` = Sector **checksum** (u16, little-endian)
  - `+0x0FF8` = Sector **signature** (u32). Bytes: `25 20 01 08`
  - `+0x0FFC` = Save **counter** (u32, little-endian)

Only sectors with the correct **signature** and **checksum** are considered valid.

---

## Step 2 — Key facts for THIS ROM (current build)

For the current build, the **verified** location of `FLAG_FLAG8_BRIDGE_SET (0x4EE)` is:

- Sector **ID = 2**
- Byte offset inside sector data: **0x38D**
- Bit mask: **0x40**

So the patch is:

- `sector2.data[0x38D] |= 0x40`

Do this in **Slot 0** and **Slot 1** for maximum reliability.

---

## Step 3 — Find sector ID 2 in the save file (rotation-safe)

### Slot layout in the save file
- Slot 0 sectors are at file offsets: `0x00000 .. 0x0DFFF`
- Slot 1 sectors are at file offsets: `0x0E000 .. 0x1BFFF`

### How to locate a valid sector
For any sector base offset `S`:
1. Check signature at `S + 0x0FF8`:
   - must be bytes: `25 20 01 08`
2. Read sector ID at `S + 0x0FF4` (little-endian u16)
3. You want the one where sector ID == `0x0002`

Do this for **Slot 0** and **Slot 1**.

---

## Step 4 — Patch the byte (set the flag)

For each slot where you found a valid sector with ID `2`:

1. Go to sector base `S`
2. Go to `S + 0x38D`
3. Read the current byte
4. Set bit 6 by OR-ing with `0x40`

Examples:
- `00` → `40`
- `41` → `41` (already set)

---

## Step 5 — Recalculate and write the sector checksum (mandatory)

If you don’t update the checksum, the sector becomes invalid and the game may load the other slot.

### 5.1 Checksum algorithm (exactly as the ROM does it)

Checksum is computed over the sector’s **data region** only.

For sector ID 2 (SaveBlock1 chunk), the size is the full `0xF80` bytes.

Algorithm:
1. Interpret the first `0xF80` bytes as little-endian 32-bit words
2. Sum all words into a 32-bit accumulator
3. Final checksum (u16) is:
   - `checksum = (sum + (sum >> 16)) & 0xFFFF`

### 5.2 Where to write it
Write the resulting u16 (little-endian) to:
- `S + 0x0FF6`

Do this for each slot you patched.

---

## Step 6 — Trigger the bridge in-game (maybe)

The bridge tiles are sometimes only materialized when you interact with the sign in Bridgeroom.

1. Load the patched save.
2. Enter **Bridgeroom**.
3. Read to the **sign**.
4. If the sign shows **AUTHORIZED**, the bridge will appear immediately.

If it still shows **OFFLINE**, you likely patched the wrong file (or the emulator overwrote it after patching).

---


## Quick reference (current build)

- Flag ID: `0x4EE`
- Sector ID: `2`
- Target offset: `data[0x38D]`
- Patch:
  - `data[0x38D] |= 0x40`
- Update checksum at:
  - `sector_base + 0x0FF6`
  - checksum computed over `0xF80` bytes with:
    - `checksum = (sum32 + (sum32 >> 16)) & 0xFFFF`