Klassenzimmer6_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Klassenzimmer6_OnTransition
    map_script MAP_SCRIPT_ON_FRAME_TABLE, Klassenzimmer6_OnFrame
    .byte 0

Klassenzimmer6_OnTransition:
    goto_if_set FLAG_KLASSENZIMMER6_FIRST_ENTRY, Klassenzimmer6_OnTransition_AlreadyDone
    setvar VAR_TEMP_1, 0
    end

Klassenzimmer6_OnTransition_AlreadyDone:
    setvar VAR_TEMP_1, 1
    end

Klassenzimmer6_OnTransition_End:
    end

Klassenzimmer6_OnFrame:
    map_script_2 VAR_TEMP_1, 0, Klassenzimmer6_EventScript_FirstEntry
    .2byte 0


@ =========================================================
@ First entry cutscene
@ =========================================================
Klassenzimmer6_EventScript_FirstEntry::
    goto_if_set FLAG_KLASSENZIMMER6_FIRST_ENTRY, Klassenzimmer6_FirstEntry_End

    setvar VAR_TEMP_1, 1
    setflag FLAG_KLASSENZIMMER6_FIRST_ENTRY

    lockall
    applymovement LOCALID_PLAYER, Klassenzimmer6_Movement_PlayerEnter
    waitmovement 0
    msgbox Klassenzimmer6_Text_FirstEntry, MSGBOX_DEFAULT
    releaseall
    end

Klassenzimmer6_FirstEntry_End::
    setvar VAR_TEMP_1, 1
    end

@ =========================================================
@ Coord trigger at x1 y3
@ =========================================================
Klassenzimmer6_EventScript_LemmyStrengthTrigger::
    goto_if_set FLAG_KLASSENZIMMER6_GOT_STRENGTH_TOOL, Klassenzimmer6_Trigger_End

    lockall

    @ Wenn Lemmy sich noch nicht bewegt hat: Bewegung einmalig ausführen
    goto_if_set FLAG_KLASSENZIMMER6_LEMMY_MOVED, Klassenzimmer6_GiveStrengthTool

    applymovement LOCALID_LEMMY, Klassenzimmer6_Movement_LemmyLeft4FaceLeft
    waitmovement 0
    copyobjectxytoperm LOCALID_LEMMY
    setflag FLAG_KLASSENZIMMER6_LEMMY_MOVED

Klassenzimmer6_GiveStrengthTool:
    msgbox Klassenzimmer6_Text_LemmyStrength, MSGBOX_DEFAULT
    giveitem ITEM_STRENGTH_TOOL, 1
    compare VAR_RESULT, FALSE
    goto_if_eq Klassenzimmer6_BagFull

    setflag FLAG_KLASSENZIMMER6_GOT_STRENGTH_TOOL
    releaseall
    end

Klassenzimmer6_BagFull::
    msgbox Klassenzimmer6_Text_BagFull, MSGBOX_DEFAULT
    releaseall
    end

Klassenzimmer6_Trigger_End::
    end

Klassenzimmer6_EventScript_LemmyTalk::
    lock
    faceplayer

    checkitem ITEM_BATTERIES, 1
    compare VAR_RESULT, TRUE
    goto_if_eq Klassenzimmer6_LemmyTalk_WrongBatteries

    msgbox Klassenzimmer6_Text_LemmyTalk, MSGBOX_DEFAULT
    release
    end

Klassenzimmer6_LemmyTalk_WrongBatteries::
    msgbox Klassenzimmer6_Text_LemmyWrongBatteries, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Trigger: blocked until Fortree Gym defeated
@ =========================================================
Klassenzimmer6_EventScript_FindBatteriesFirst::
    goto_if_set FLAG_DEFEATED_FORTREE_GYM, Klassenzimmer6_FindBatteriesFirst_End

    lockall
    msgbox Klassenzimmer6_Text_FindBatteriesFirst, MSGBOX_DEFAULT
    applymovement LOCALID_PLAYER, Klassenzimmer6_Movement_PlayerUp1
    waitmovement 0
    releaseall
    end

Klassenzimmer6_FindBatteriesFirst_End::
    end

@ =========================================================
@ Movements
@ =========================================================
Klassenzimmer6_Movement_PlayerEnter:
    walk_left
	walk_left
    face_up
    step_end

Klassenzimmer6_Movement_LemmyLeft4FaceLeft:
    walk_left
    walk_left
    walk_left
    walk_left
    face_left
    step_end

Klassenzimmer6_Movement_PlayerUp1:
    walk_up
	face_up
    step_end


@ =========================================================
@ Text
@ =========================================================
Klassenzimmer6_Text_FirstEntry:
	.string "LEMMY: {PLAYER}, can you please\n"
	.string "get me a pack of batteries from\p"
	.string "the storage room here on the left?$"

Klassenzimmer6_Text_LemmyStrength:
    .string "LEMMY: Here, you'll need this.$"

Klassenzimmer6_Text_BagFull:
    .string "Your BAG is full.$"

Klassenzimmer6_Text_LemmyTalk:
    .string "LEMMY: Have you got the\n"
	.string "batteries yet?$"

Klassenzimmer6_Text_LemmyWrongBatteries:
	.string "LEMMY: These batteries are the\n"
	.string "wrong size. Please find the\p"
	.string "others.$"

Klassenzimmer6_Text_FindBatteriesFirst:
    .string "I should find the batteries first.$"



