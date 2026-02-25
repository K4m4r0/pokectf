#  “Mantis Memory” Puzzle — Step-by-step (mGBA Standalone)

This guide assumes you are using **mGBA Standalone** (not RetroArch).

## Goal
You must **change a value in RAM** while the game is running.  
When done correctly, a **hidden console** appears and reveals **CTF Flag #5**.

---

## 1) Start the game and reach the puzzle room
1. Open the ROM in **mGBA Standalone**.
2. Load your save and travel to the map called **`entryMapFlag7`**.
3. Talk to the NPC (the “Mantis” character) once if you want flavor text.

---

## 2) Open the mGBA Log window (you need this hint)
1. In mGBA, open:
   - **Tools → View logs…**
2. Make sure the log window is visible and "Warning" is checked.
3. Re-enter the map **entryMapFlag7** (or simply enter it once after launching the ROM).

### What you should see in the log
You should find a line similar to:

- `[MANTIS] entryMapFlag7: ...`

This line tells you what value you must search for in memory and what to change it to.

---

## 3) Open Memory Search in mGBA
1. In mGBA, open the memory search tool:
   - **Tools → Game state views → Search memory…**
2. Configure the search:
   - **Value type:** `16-bit` (sometimes called “Halfword”)
   - **Value:** `0xBEEF`
   - **Region (if selectable):** `EWRAM`

3. Run the search.

> If you get many results, try leaving and re-entering the map once and search again.  
> The game sets the value when the map loads.

---

## 4) Edit the found memory value to solve the puzzle
1. From the search results, open a matching address in the **Memory Viewer**.
2. Confirm the current **16-bit** value at that location is `0xBEEF`.
2a. It might appear as little endian. Be sure to change it accordingly.
3. Change that **exact 16-bit value** to:

- `0x1337`

4. Apply/confirm the change (depending on the UI).

---

## 5) Verify the puzzle triggered
If you changed the correct value:
- You will hear a sound and/or see a message.
- A previously hidden **console object** appears on the map.

Walk to the console and press **A** to interact.

---

## 6) Read the flag
The console will display:

- `CTF Flag 5: STACK`

That is the solution you submit for this challenge.

---

## Troubleshooting

### I don’t see the log message
- Make sure you are in **mGBA Standalone** (not RetroArch).
- Open **Tools → View logs…**
- Re-enter **entryMapFlag7** after opening the log window.

### Memory search finds nothing
- Ensure search is **16-bit** and value is **0xBEEF**.
- Re-enter the map so the value is set again.
- Try searching in **EWRAM** if the tool lets you choose regions.

### I changed a value but nothing happened
- You may have edited the wrong result. Search again and verify you are editing a **16-bit** `0xBEEF`.
- Make sure you changed it to **exactly** `0x1337` (hex).
- Make sure you changed it in little endian formatting. If it appears as EF BE change to 37 13