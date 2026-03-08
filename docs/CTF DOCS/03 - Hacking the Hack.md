# Pokémon Capture the Flag – Hacking the Hack

In this document, we describe the things that were not generally intended or provided by the decompilation and ROM hack and were programmed by ourselves. We do not go into things that the hack generally offers but have been misused and modified.

## Implemented additions and changes

- **Complete conversion of the title screen (Press Start Screen)** from 16 colors to 256 colors.
- **Installation of the terminal mechanism**, which allows words to be entered during gameplay and thus checks the correctness of the **FLAGS**.
- **Installation of a method to link items with 256-color images** and display them.
- **Function installed to hide an image in the code of the ROM hack** in order to perform steganography.
- **Function built in that securely stores predefined words** in the hex output of savegames.
- **Fake trade events built in** to evolve Pokémon that would otherwise only evolve through physical trading with another person.
- **Function built in that makes opposing Pokémon trainers react** to Pokémon on your own team and changes the text output accordingly (optionally also the battle AI).
- **mGBA use detection**, a script that checks the use of the mGBA emulator and causes NPCs to react accordingly. When using mGBA, if the player is in a certain location, an output is triggered in the mGBA log file, which gives a hint about a flag.
- **Edited the Moving Boulder Logic** to move other world objects with strength aswell.