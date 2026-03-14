CH2_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, CH2_OnLoad
    .byte 0

    .equ CH2_OPEN_TOP_TILE, 0x202


@ =========================================================
@ OnLoad: Weg offen halten, wenn Chad besiegt wurde
@ =========================================================
CH2_OnLoad:
    checktrainerflag TRAINER_CHAD
    goto_if_eq VAR_RESULT, TRUE, CH2_OpenPassage
    end

CH2_OpenPassage:
    setmetatile 9, 2, CH2_OPEN_TOP_TILE, FALSE
    special DrawWholeMapView
    end


@ =========================================================
@ RENE
@ =========================================================
CH2_EventScript_Rene::
    lock
    faceplayer

    checktrainerflag TRAINER_CHAD
    goto_if_eq VAR_RESULT, TRUE, CH2_EventScript_Rene_After

    msgbox CH2_Text_ReneIntro, MSGBOX_DEFAULT
    closemessage

    trainerbattle_single TRAINER_CHAD, CH2_Text_ReneBattleIntro, CH2_Text_ReneBattleDefeat, CH2_EventScript_Rene_AfterBattle
    end

CH2_EventScript_Rene_AfterBattle::
    msgbox CH2_Text_ReneAfterBattle, MSGBOX_DEFAULT
    closemessage

    setmetatile 9, 2, CH2_OPEN_TOP_TILE, FALSE
    special DrawWholeMapView

    releaseall
    end

CH2_EventScript_Rene_After::
    msgbox CH2_Text_ReneAfter, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Texte
@ =========================================================
CH2_Text_ReneIntro:
    .string "RENE: So you made it to the second\n"
    .string "room of the Challenge House.\p"
    .string "The further you go, the tougher it\n"
    .string "gets.\p"
    .string "Let's see whether you can make it\n"
    .string "past me as well.$"

CH2_Text_ReneBattleIntro:
    .string "RENE: Show me that your first win\n"
    .string "wasn't just luck.$"

CH2_Text_ReneBattleDefeat:
    .string "RENE: Not bad. You've earned your\n"
    .string "next step.$"

CH2_Text_ReneAfterBattle:
    .string "RENE: Impressive.\p"
    .string "The path to the next room is now open.$"

CH2_Text_ReneAfter:
    .string "RENE: Keep going.\p"
    .string "The real challenge is still ahead.$"

