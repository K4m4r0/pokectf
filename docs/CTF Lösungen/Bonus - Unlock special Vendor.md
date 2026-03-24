# Unlocking the Secret Vendor

Follow these steps to unlock the secret vendor in **mGBA**.

## Requirements

You need:

- the **ROM**
- the file **`ctf_vendor_unlock.lua`**
- **mGBA**

Important:

- **`ctf_vendor_unlock.lua`** must be placed in the **same folder as the ROM**.
- The unlock file must be named **`open_sesame.txt`**.
- The **content of the file does not matter**.
- Once the unlock has been detected, the vendor stays **permanently unlocked**.

---

## Step-by-step instructions

### 1. Prepare the ROM folder

Place the following files in the **same folder**:

- `pokectf.gba`
- `ctf_vendor_unlock.lua`


---

### 2. Start the ROM in mGBA

Open **mGBA** and launch your ROM.

---

### 3. Load the Lua script

In mGBA, open:

**Tools -> Scripting...**

Then load the file:

`ctf_vendor_unlock.lua`

The script will now monitor the ROM folder for the unlock file.

---

### 4. Go to the secret vendor

Travel to the map that contains the secret vendor.

If the vendor is still locked, he will say:

> Hey kid, there you are again. Do you like your POKéMON? To get access to the rest of my products, you have to store the code word correctly.

There is also a hint NPC who says:

> Psst, one thousand and one nights. You didn't hear that from me.

---

### 5. Create the unlock file

Create a file in the **same folder as the ROM** with exactly this name:

`open_sesame.txt`

Important:

- The filename must match **exactly**.
- The content of the file does **not** matter.
- The file extension must be **`.txt`**.

---

### 6. Let the game detect the file

As soon as `open_sesame.txt` exists in the ROM folder and the Lua script is loaded, the unlock can be detected.

If you are already standing on the vendor map, simply talk to the vendor again.

---

### 7. Permanently unlock the vendor

When the unlock is detected for the first time, the following happens:

- the unlock is consumed
- the extra tiles are changed and become walkable
- the vendor is permanently unlocked

The vendor will then say:

> You are a smart kid. Please enjoy my supplies.

After that, his special menu opens.

---

## Reward

At the moment, the vendor offers this reward:

- **100x RARE CANDY**

This option is:

- **free**
- **repeatable**
- only limited by available bag space

If your Bag does not have enough space, you must make room first.

---

## Important note

The unlock is **persistent**.

That means:

- You only need to place `open_sesame.txt` **once**.
- After that, the vendor remains unlocked even if you:
  - delete the file
  - restart mGBA
  - reload the save

---

## Quick summary

1. Put the ROM and `ctf_vendor_unlock.lua` in the same folder.
2. Start the ROM in mGBA.
3. In mGBA, open **Tools -> Scripting...** and load `ctf_vendor_unlock.lua`.
4. Create `open_sesame.txt` in the same folder as the ROM.
5. Talk to the vendor again.
6. The unlock is saved permanently.

---

## Common mistakes

If it does not work, check the following:

- Is `ctf_vendor_unlock.lua` really in the same folder as the ROM?
- Did you actually load the Lua script in mGBA?
- Is the file really named exactly `open_sesame.txt`?
- Is it accidentally named `open_sesame.txt.txt`?
- Is the file really in the ROM folder and not somewhere else?

---

## Find correct address

arm-none-eabi-nm -n pokeemerald.elf | grep gCtfVendorUnlockMagic