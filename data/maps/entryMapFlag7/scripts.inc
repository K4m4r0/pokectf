entryMapFlag7_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, entryMapFlag7_OnLoad
    map_script MAP_SCRIPT_ON_FRAME_TABLE, entryMapFlag7_OnFrameTable
    .byte 0

entryMapFlag7_OnFrameTable:
    map_script_2 VAR_UNUSED_0x8014, 0x1337, entryMapFlag7_EventScript_OnSolved
    .2byte 0

entryMapFlag7_OnLoad:
    setflag FLAG_TEMP_5
    setvar VAR_UNUSED_0x8014, 0xBEEF

    special CtfIsMgba
    goto_if_eq VAR_RESULT, 1, entryMapFlag7_OnLoad_LogHint
    end

entryMapFlag7_OnLoad_LogHint:
    special CtfMgbaLogHint_Flag5
    end

entryMapFlag7_EventScript_MantisNPC::
    lock
    faceplayer
    special CtfIsMgba
    goto_if_eq VAR_RESULT, 1, entryMapFlag7_MantisText_Mgba
    msgbox entryMapFlag7_Text_Mantis_Other, MSGBOX_DEFAULT
    release
    end

entryMapFlag7_MantisText_Mgba:
    msgbox entryMapFlag7_Text_Mantis_Mgba, MSGBOX_DEFAULT
    release
    end

entryMapFlag7_EventScript_OnSolved::
    setvar VAR_UNUSED_0x8014, 0
    clearflag FLAG_TEMP_5

    playse SE_M_SACRED_FIRE
    waitse
    msgbox entryMapFlag7_Text_Reveal, MSGBOX_DEFAULT
    release
    end

entryMapFlag7_EventScript_MantisConsole::
    lock
    faceplayer
    setvar VAR_0x8004, 5
    special CtfBufferFlagSolution
    msgbox entryMapFlag7_Text_Console, MSGBOX_DEFAULT
    release
    end

@ -----------------------
@ Texte
@ -----------------------
entryMapFlag7_Text_Mantis_Mgba::
	.string "I sense that you use the correct\n"
	.string "tool called mGBA. Open your Logs!$"

entryMapFlag7_Text_Mantis_Other::
	.string "What?! I cannot read you!! \n"
	.string "You are not using the correct \p"
	.string "tool to enter this world.$"

entryMapFlag7_Text_Reveal::
    .string "...you touched the memory.\n"
    .string "Something is materializing.$"

entryMapFlag7_Text_Console::
    .string "KONSOLE:\n"
	.string "CTF FLAG 5: STACK$"

