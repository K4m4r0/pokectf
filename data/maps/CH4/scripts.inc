CH4_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, CH4_OnLoad
    .byte 0

    .equ CH4_OPEN_TOP_TILE, 0x202


@ =========================================================
@ OnLoad: Weg offen halten, wenn Cora besiegt wurde
@ =========================================================
CH4_OnLoad:
    checktrainerflag TRAINER_CORA
    goto_if_eq VAR_RESULT, TRUE, CH4_OpenPassage
    end

CH4_OpenPassage:
    setmetatile 9, 2, CH4_OPEN_TOP_TILE, FALSE
    special DrawWholeMapView
    end


@ =========================================================
@ CORA
@ =========================================================
CH4_EventScript_Cora::
    lock
    faceplayer

    checktrainerflag TRAINER_CORA
    goto_if_eq VAR_RESULT, TRUE, CH4_EventScript_Cora_After

    msgbox CH4_Text_CoraIntro, MSGBOX_DEFAULT
    closemessage

    trainerbattle_single TRAINER_CORA, CH4_Text_CoraBattleIntro, CH4_Text_CoraBattleDefeat, CH4_EventScript_Cora_AfterBattle
    end

CH4_EventScript_Cora_AfterBattle::
    msgbox CH4_Text_CoraAfterBattle, MSGBOX_DEFAULT
    closemessage

    setmetatile 9, 2, CH4_OPEN_TOP_TILE, FALSE
    special DrawWholeMapView

    releaseall
    end

CH4_EventScript_Cora_After::
    msgbox CH4_Text_CoraAfter, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Texte
@ =========================================================
CH4_Text_CoraIntro:
    .string "DUDE: You've made it farther than\n"
    .string "most challengers ever do.\p"
    .string "But every room is designed to test\n"
    .string "something different.\p"
    .string "Let's see whether you can clear\n"
    .string "this one too.$"

CH4_Text_CoraBattleIntro:
    .string "DUDE: Show me that your run through\n"
    .string "the Challenge House is no fluke.$"

CH4_Text_CoraBattleDefeat:
    .string "DUDE: Impressive. You may proceed.$"

CH4_Text_CoraAfterBattle:
    .string "DUDE: Well fought.\p"
    .string "The path to the next room is now open.$"

CH4_Text_CoraAfter:
    .string "DUDE: Keep going.\p"
    .string "The prize is getting closer.$"

