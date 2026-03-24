CH6_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, CH6_OnLoad
    .byte 0

    .equ CH6_OPEN_TOP_TILE, 0x202


@ =========================================================
@ OnLoad: Weg offen halten, wenn Georgia besiegt wurde
@ =========================================================
CH6_OnLoad:
    checktrainerflag TRAINER_GEORGIA
    goto_if_eq VAR_RESULT, TRUE, CH6_OpenPassage
    end

CH6_OpenPassage:
    setmetatile 9, 2, CH6_OPEN_TOP_TILE, FALSE
    special DrawWholeMapView
    end


@ =========================================================
@ GEORGIA
@ =========================================================
CH6_EventScript_Georgia::
    lock
    faceplayer

    checktrainerflag TRAINER_GEORGIA
    goto_if_eq VAR_RESULT, TRUE, CH6_EventScript_Georgia_After

    msgbox CH6_Text_GeorgiaIntro, MSGBOX_DEFAULT
    closemessage

    trainerbattle_single TRAINER_GEORGIA, CH6_Text_GeorgiaBattleIntro, CH6_Text_GeorgiaBattleDefeat, CH6_EventScript_Georgia_AfterBattle
    end

CH6_EventScript_Georgia_AfterBattle::
    msgbox CH6_Text_GeorgiaAfterBattle, MSGBOX_DEFAULT
    closemessage

    setmetatile 9, 2, CH6_OPEN_TOP_TILE, FALSE
    special DrawWholeMapView

    releaseall
    end

CH6_EventScript_Georgia_After::
    msgbox CH6_Text_GeorgiaAfter, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Texte
@ =========================================================
CH6_Text_GeorgiaIntro:
    .string "NATE: Room six.\p"
    .string "At this point, luck is no longer\n"
    .string "enough to carry anyone.\p"
    .string "Only challengers with real discipline\n"
    .string "make it this far.$"

CH6_Text_GeorgiaBattleIntro:
    .string "NATE: Let's see whether your focus\n"
    .string "holds under pressure.$"

CH6_Text_GeorgiaBattleDefeat:
    .string "NATE: Very good. You've earned the\n"
    .string "right to continue.$"

CH6_Text_GeorgiaAfterBattle:
    .string "NATE: Well fought.\p"
    .string "The next room is open to you.$"

CH6_Text_GeorgiaAfter:
    .string "NATE: Keep going.\p"
    .string "The end is close, but not close\n"
    .string "enough.$"

