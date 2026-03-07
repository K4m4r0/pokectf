Flagroom5_2_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, Flagroom5_2_OnLoad
    map_script MAP_SCRIPT_ON_FRAME_TABLE, Flagroom5_2_OnFrameTable
    .byte 0

Flagroom5_2_OnFrameTable:
    map_script_2 VAR_UNUSED_0x8014, 0x1337, Flagroom5_2_EventScript_OnSolved
    .2byte 0

Flagroom5_2_OnLoad:
    setvar VAR_UNUSED_0x8014, 0xBEEF

    @ Konsole/Pokédex sichtbar oder versteckt?
    goto_if_set FLAG_FLAGROOM5_2_CONSOLE_REVEALED, Flagroom5_2_OnLoad_ShowConsole

Flagroom5_2_OnLoad_HideConsole:
    setflag FLAG_TEMP_5
    goto Flagroom5_2_OnLoad_CheckUnlock

Flagroom5_2_OnLoad_ShowConsole:
    clearflag FLAG_TEMP_5

Flagroom5_2_OnLoad_CheckUnlock:
    @ Wenn schon freigeschaltet: Tiles setzen
    goto_if_set FLAG_FLAGROOM5_2_FLAG5_UNLOCKED, Flagroom5_2_OnLoad_ApplyTiles

    special CtfIsMgba
    goto_if_eq VAR_RESULT, 1, Flagroom5_2_OnLoad_LogHint
    end

Flagroom5_2_OnLoad_ApplyTiles:
    call Flagroom5_2_EventScript_ApplyFlag5Tiles

    special CtfIsMgba
    goto_if_eq VAR_RESULT, 1, Flagroom5_2_OnLoad_LogHint
    end

Flagroom5_2_OnLoad_LogHint:
    special CtfMgbaLogHint_Flag5
    end

@ -----------------------
@ NPC (Mantis)
@ -----------------------
Flagroom5_2_EventScript_MantisNPC::
    lock
    faceplayer
    special CtfIsMgba
    goto_if_eq VAR_RESULT, 1, Flagroom5_2_MantisText_Mgba
    msgbox Flagroom5_2_Text_Mantis_Other, MSGBOX_DEFAULT
    release
    end

Flagroom5_2_MantisText_Mgba:
    msgbox Flagroom5_2_Text_Mantis_Mgba, MSGBOX_DEFAULT
    release
    end

@ -----------------------
@ SOLVED (Memory/Frame-Table Trigger)
@ -----------------------
Flagroom5_2_EventScript_OnSolved::
    setvar VAR_UNUSED_0x8014, 0
    setflag FLAG_FLAGROOM5_2_CONSOLE_REVEALED
    clearflag FLAG_TEMP_5

    @ Konsole sofort erscheinen lassen
    addobject LOCALID_MANTIS_CONSOLE

    playse SE_M_SACRED_FIRE
    waitse
    msgbox Flagroom5_2_Text_Reveal, MSGBOX_DEFAULT
    release
    end

@ -----------------------
@ Output-Console (zeigt Lösung / Debug)
@ -----------------------
Flagroom5_2_EventScript_MantisConsole::
    lock
    faceplayer
    setvar VAR_0x8004, 5
    special CtfBufferFlagSolution
    msgbox Flagroom5_2_Text_Console, MSGBOX_DEFAULT
    release
    end

@ =========================================================
@ CTF Terminal (Flag 5) - Flagroom5_2
@ =========================================================

Flagroom5_2_EventScript_CtfTerminal_Flag5::
    lock
    faceplayer

    goto_if_set FLAG_FLAGROOM5_2_FLAG5_UNLOCKED, Flagroom5_2_Terminal_AlreadySolved

    msgbox Flagroom5_2_Text_TerminalPrompt, MSGBOX_DEFAULT
    closemessage

    setvar VAR_0x8000, 5
    callnative Ctf_FlagTerminal
    waitstate

    compare VAR_RESULT, TRUE
    goto_if_eq Flagroom5_2_Terminal_Correct

    msgbox Flagroom5_2_Text_TerminalWrong, MSGBOX_DEFAULT
    release
    end

Flagroom5_2_Terminal_Correct:
    setflag FLAG_FLAGROOM5_2_FLAG5_UNLOCKED
    call Flagroom5_2_EventScript_ApplyFlag5Tiles
    msgbox Flagroom5_2_Text_TerminalCorrect, MSGBOX_DEFAULT
    release
    end

Flagroom5_2_Terminal_AlreadySolved:
    msgbox Flagroom5_2_Text_TerminalAlreadySolved, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Signs
@ =========================================================

Flagroom5_2_BrailleWall::
    lockall
    braillemsgbox Flagroom5_2_Text_Braille
    releaseall
    end


@ =========================================================
@ Tile Swap (3x3, instant sichtbar + begehbar)
@ =========================================================

Flagroom5_2_EventScript_ApplyFlag5Tiles::
    setmetatile 8,  8,  0x188, FALSE
    setmetatile 8,  9,  0x188, FALSE
    setmetatile 8,  10, 0x188, FALSE
    setmetatile 9,  8,  0x188, FALSE
    setmetatile 9,  9,  0x188, FALSE
    setmetatile 9,  10, 0x188, FALSE
    setmetatile 10, 8,  0x188, FALSE
    setmetatile 10, 9,  0x188, FALSE
    setmetatile 10, 10, 0x188, FALSE
    special DrawWholeMapView
    return


@ =========================================================
@ Terminal Texte
@ =========================================================


Flagroom5_2_Text_Mantis_Mgba::
    .string "I sense that you use the correct\n"
    .string "tool called mGBA. Open your Logs!$"

Flagroom5_2_Text_Mantis_Other::
    .string "What?! I cannot read you!! \n"
    .string "You are not using the correct \p"
    .string "tool to enter this world.$"

Flagroom5_2_Text_Reveal::
    .string "...you touched the memory.\n"
    .string "Something is materializing.$"

Flagroom5_2_Text_Console::
    .string "KONSOLE:\n"
    .string "CTF FLAG 5: STACK$"

Flagroom5_2_Text_TerminalPrompt::
    .string "TERMINAL:\n"
    .string "Enter CTF FLAG 5.$"

Flagroom5_2_Text_TerminalWrong::
    .string "TERMINAL:\n"
    .string "ACCESS DENIED.$"

Flagroom5_2_Text_TerminalCorrect::
    .string "TERMINAL:\n"
    .string "ACCESS GRANTED.$"

Flagroom5_2_Text_TerminalAlreadySolved::
    .string "TERMINAL:\n"
    .string "ALREADY UNLOCKED.$"

Flagroom5_2_Text_Braille::
    brailleformat 0, 0, 0, 0, 0, 0
    .braille "mGBA$"

