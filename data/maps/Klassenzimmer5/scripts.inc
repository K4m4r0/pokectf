Klassenzimmer5_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Klassenzimmer5_OnTransition
    .byte 0

    .equ CMP_EQ, 1
    .equ CMP_NE, 5

@ =========================================================
@ First entry text (once)
@ =========================================================
Klassenzimmer5_OnTransition::
    checkflag FLAG_KLASSENZIMMER5_FIRST_ENTRY
    compare VAR_RESULT, 1
    goto_if CMP_EQ, Klassenzimmer5_OnTransition_End

    setflag FLAG_KLASSENZIMMER5_FIRST_ENTRY
    lockall
    msgbox Klassenzimmer5_Text_FirstEntry, MSGBOX_DEFAULT
    releaseall
Klassenzimmer5_OnTransition_End::
    end

@ =========================================================
@ Cut Tool pickup
@ =========================================================
Klassenzimmer5_EventScript_GetCutTool::
    lock
    faceplayer

    checkflag FLAG_KLASSENZIMMER5_GOT_CUT_TOOL
    compare VAR_RESULT, 1
    goto_if CMP_EQ, Klassenzimmer5_GetCutTool_Already

    giveitem ITEM_CUT_TOOL, 1
    compare VAR_RESULT, 0
    goto_if CMP_EQ, Klassenzimmer5_GetCutTool_NoRoom

    setflag FLAG_KLASSENZIMMER5_GOT_CUT_TOOL
    msgbox Klassenzimmer5_Text_GotCutTool, MSGBOX_DEFAULT

    @ Optional: Objekt verschwinden lassen (wenn du willst)
    @ removeobject LOCALID_CUT_TOOL

    release
    end

Klassenzimmer5_GetCutTool_NoRoom::
    msgbox Klassenzimmer5_Text_NoRoom, MSGBOX_DEFAULT
    release
    end

Klassenzimmer5_GetCutTool_Already::
    msgbox Klassenzimmer5_Text_Empty, MSGBOX_DEFAULT
    release
    end

@ =========================================================
@ Text
@ =========================================================
Klassenzimmer5_Text_FirstEntry:
    .string "No one here? What's going on?\n"
    .string "I'd better check the schedule.\p"
    .string "... ... ...\n"
    .string "Great, today's lecture is canceled...$"

Klassenzimmer5_Text_GotCutTool:
	.string "Hmm, someone must have lost this.$"
    .string "You found the PRUNING SHEARS!$"

Klassenzimmer5_Text_NoRoom:
    .string "Your bag is full.$"

Klassenzimmer5_Text_Empty:
    .string "Nothing left here.$"

