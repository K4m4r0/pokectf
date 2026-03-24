CH5_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, CH5_OnLoad
    .byte 0

    .equ CH5_OPEN_TOP_TILE, 0x202


@ =========================================================
@ OnLoad: Weg offen halten, wenn Berke besiegt wurde
@ =========================================================
CH5_OnLoad:
    checktrainerflag TRAINER_BERKE
    goto_if_eq VAR_RESULT, TRUE, CH5_OpenPassage
    end

CH5_OpenPassage:
    setmetatile 9, 2, CH5_OPEN_TOP_TILE, FALSE
    special DrawWholeMapView
    end


@ =========================================================
@ BERKE
@ =========================================================
CH5_EventScript_Berke::
    lock
    faceplayer

    checktrainerflag TRAINER_BERKE
    goto_if_eq VAR_RESULT, TRUE, CH5_EventScript_Berke_After

    msgbox CH5_Text_BerkeIntro, MSGBOX_DEFAULT
    closemessage

    trainerbattle_single TRAINER_BERKE, CH5_Text_BerkeBattleIntro, CH5_Text_BerkeBattleDefeat, CH5_EventScript_Berke_AfterBattle
    end

CH5_EventScript_Berke_AfterBattle::
    msgbox CH5_Text_BerkeAfterBattle, MSGBOX_DEFAULT
    closemessage

    setmetatile 9, 2, CH5_OPEN_TOP_TILE, FALSE
    special DrawWholeMapView

    releaseall
    end

CH5_EventScript_Berke_After::
    msgbox CH5_Text_BerkeAfter, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Texte
@ =========================================================
CH5_Text_BerkeIntro:
    .string "JOHNSON: You've come a long way.\p"
    .string "Most challengers break before they\n"
    .string "ever reach room five.\p"
    .string "Let's see whether your streak ends\n"
    .string "here.$"

CH5_Text_BerkeBattleIntro:
    .string "JOHNSON: Show me the strength that got\n"
    .string "you this far.$"

CH5_Text_BerkeBattleDefeat:
    .string "JOHNSON: Hah. You earned that win.$"

CH5_Text_BerkeAfterBattle:
    .string "JOHNSON: Impressive.\p"
    .string "The way ahead is open.$"

CH5_Text_BerkeAfter:
    .string "JOHNSON: One step at a time.\p"
    .string "The Challenge House isn't done with\n"
    .string "you yet.$"

