CH1_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, CH1_OnLoad
    .byte 0

    .equ CH1_OPEN_TOP_TILE, 0x202


@ =========================================================
@ OnLoad: Weg offen halten, wenn Dudley besiegt wurde
@ =========================================================
CH1_OnLoad:
    checktrainerflag TRAINER_DUDLEY
    goto_if_eq VAR_RESULT, TRUE, CH1_OpenPassage
    end

CH1_OpenPassage:
    setmetatile 9, 2, CH1_OPEN_TOP_TILE, FALSE
    special DrawWholeMapView
    end


@ =========================================================
@ ILJA
@ =========================================================
CH1_EventScript_Ilja::
    lock
    faceplayer

    checktrainerflag TRAINER_DUDLEY
    goto_if_eq VAR_RESULT, TRUE, CH1_EventScript_Ilja_After

    msgbox CH1_Text_IljaIntro, MSGBOX_DEFAULT
    closemessage

    trainerbattle_single TRAINER_DUDLEY, CH1_Text_DudleyIntro, CH1_Text_DudleyDefeat, CH1_EventScript_Ilja_AfterBattle
    end

CH1_EventScript_Ilja_AfterBattle::
    msgbox CH1_Text_IljaAfterBattle, MSGBOX_DEFAULT
    closemessage

    setmetatile 9, 2, CH1_OPEN_TOP_TILE, FALSE
    special DrawWholeMapView

    releaseall
    end

CH1_EventScript_Ilja_After::
    msgbox CH1_Text_IljaAfter, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Texte
@ =========================================================
CH1_Text_IljaIntro:
    .string "ILJA: Welcome to the first room of\n"
    .string "the Challenge House.\p"
    .string "Beat every champion and the prize\n"
    .string "at the end will be worth it.\p"
    .string "Let's see if you can make it past\n"
    .string "me first.$"

CH1_Text_DudleyIntro:
    .string "ILJA: In this house, only the strong\n"
    .string "move forward.$"

CH1_Text_DudleyDefeat:
    .string "ILJA: Hm. You've earned the right\n"
    .string "to continue.$"

CH1_Text_IljaAfterBattle:
    .string "ILJA: Well done.\p"
    .string "The path to the next room is now open.$"

CH1_Text_IljaAfter:
    .string "ILJA: One champion down.\p"
    .string "Keep going if you want to claim the\n"
    .string "final prize.$"

