Klassenzimmer_Last_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, Klassenzimmer_Last_OnLoad
    map_script MAP_SCRIPT_ON_TRANSITION, Klassenzimmer_Last_OnTransition
    map_script MAP_SCRIPT_ON_FRAME_TABLE, Klassenzimmer_Last_OnFrame
    .byte 0


@ =========================================================
@ OnLoad
@ =========================================================
Klassenzimmer_Last_OnLoad:
    goto_if_set FLAG_KLASSENZIMMER_LAST_INTRO_DONE, Klassenzimmer_Last_OnLoad_ShowWidefield

    setflag FLAG_HIDE_KLASSENZIMMER_LAST_WIDEFIELD
    removeobject LOCALID_WIDEFIELD
    end

Klassenzimmer_Last_OnLoad_ShowWidefield:
    clearflag FLAG_HIDE_KLASSENZIMMER_LAST_WIDEFIELD
    end


@ =========================================================
@ OnTransition / OnFrame
@ =========================================================
Klassenzimmer_Last_OnTransition:
    goto_if_set FLAG_KLASSENZIMMER_LAST_INTRO_DONE, Klassenzimmer_Last_OnTransition_AlreadyDone
    setvar VAR_TEMP_0, 0
    end

Klassenzimmer_Last_OnTransition_AlreadyDone:
    setvar VAR_TEMP_0, 1
    end

Klassenzimmer_Last_OnFrame:
    map_script_2 VAR_TEMP_0, 0, Klassenzimmer_Last_EventScript_FirstEntry
    .2byte 0


@ =========================================================
@ First entry cutscene
@ =========================================================
Klassenzimmer_Last_EventScript_FirstEntry::
    setvar VAR_TEMP_0, 1
    setflag FLAG_KLASSENZIMMER_LAST_INTRO_DONE

    lockall

    applymovement LOCALID_PLAYER, Klassenzimmer_Last_Movement_PlayerIntro
    waitmovement 0

    clearflag FLAG_HIDE_KLASSENZIMMER_LAST_WIDEFIELD
    addobject LOCALID_WIDEFIELD

    msgbox Klassenzimmer_Last_Text_WidefieldGreeting, MSGBOX_DEFAULT
    closemessage

    applymovement LOCALID_WIDEFIELD, Klassenzimmer_Last_Movement_WidefieldEnter
    waitmovement 0
    copyobjectxytoperm LOCALID_WIDEFIELD

    msgbox Klassenzimmer_Last_Text_WidefieldSpeech, MSGBOX_DEFAULT
    closemessage

    giveitem ITEM_RNV_TICKET, 1

    releaseall
    end


@ =========================================================
@ Widefield talk
@ =========================================================
Klassenzimmer_Last_EventScript_WidefieldTalk::
    lock
    faceplayer
    msgbox Klassenzimmer_Last_Text_WidefieldAfter, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Movements
@ =========================================================
Klassenzimmer_Last_Movement_PlayerIntro:
    walk_up
    walk_up
    walk_left
    walk_left
    face_up
    step_end

Klassenzimmer_Last_Movement_WidefieldEnter:
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_left
    walk_left
    face_down
    step_end


@ =========================================================
@ Text
@ =========================================================
Klassenzimmer_Last_Text_WidefieldGreeting:
    .string "WIDEFIELD: Good morning students!$"

Klassenzimmer_Last_Text_WidefieldSpeech:
    .string "WIDEFIELD: Congratulations,\n"
    .string "students. You've made it to your\p"
    .string "final semester.\p"
    .string "For your last assignment, you need\n"
    .string "to see PROF. FARMER and pass his\p"
    .string "exam.\p"
    .string "You'll find him in the WATER TOWER.\n"
    .string "To get there, you'll need this\p"
    .string "RNV TICKET to take the tram.\p"
    .string "Good luck to all of you!$"

Klassenzimmer_Last_Text_WidefieldAfter:
    .string "WIDEFIELD: Good luck on your\n"
    .string "final exam!$"

