CH7_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, CH7_OnLoad
    .byte 0

    .equ CH7_OPEN_TOP_TILE, 0x202


@ =========================================================
@ OnLoad: Weg offen halten, wenn Nancy besiegt wurde
@ =========================================================
CH7_OnLoad:
    checktrainerflag TRAINER_NANCY
    goto_if_eq VAR_RESULT, TRUE, CH7_OpenPassage
    end

CH7_OpenPassage:
    setmetatile 9, 2, CH7_OPEN_TOP_TILE, FALSE
    special DrawWholeMapView
    end


@ =========================================================
@ NANCY
@ =========================================================
CH7_EventScript_Nancy::
    lock
    faceplayer

    checktrainerflag TRAINER_NANCY
    goto_if_eq VAR_RESULT, TRUE, CH7_EventScript_Nancy_After

    msgbox CH7_Text_NancyIntro, MSGBOX_DEFAULT
    closemessage

    trainerbattle_single TRAINER_NANCY, CH7_Text_NancyBattleIntro, CH7_Text_NancyBattleDefeat, CH7_EventScript_Nancy_AfterBattle
    end

CH7_EventScript_Nancy_AfterBattle::
    msgbox CH7_Text_NancyAfterBattle, MSGBOX_DEFAULT
    closemessage

    setmetatile 9, 2, CH7_OPEN_TOP_TILE, FALSE
    special DrawWholeMapView

    releaseall
    end

CH7_EventScript_Nancy_After::
    msgbox CH7_Text_NancyAfter, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Texte
@ =========================================================
CH7_Text_NancyIntro:
    .string "FRED: So you stand before the final\n"
    .string "door of the Challenge House.\p"
    .string "Every room behind you was a test of\n"
    .string "skill, resolve, and endurance.\p"
    .string "But the last step is always the\n"
    .string "hardest.\p"
    .string "Come. Show me the strength that brought\n"
    .string "you all this way.$"

CH7_Text_NancyBattleIntro:
    .string "FRED: Let this final battle decide\n"
    .string "whether you are truly worthy!$"

CH7_Text_NancyBattleDefeat:
    .string "FRED: Magnificent...\p"
    .string "You have conquered the Challenge\n"
    .string "House.$"

CH7_Text_NancyAfterBattle:
    .string "FRED: Glorious work.\p"
    .string "You fought with courage and proved\n"
    .string "yourself to every champion here.\p"
    .string "The path to your reward is now open.$"

CH7_Text_NancyAfter:
    .string "FRED: Go on, champion.\p"
    .string "Claim the prize you have earned.$"

