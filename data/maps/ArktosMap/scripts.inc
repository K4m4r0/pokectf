ArktosMap_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, ArktosMap_OnTransition
    .byte 0

    .equ ARTICUNO_LEVEL, 30


@ =========================================================
@ Beim Betreten der Höhle
@ =========================================================
ArktosMap_OnTransition::
    setflag FLAG_ARKTOS_MAP_BETRETEN
    end


@ =========================================================
@ Darkness blocker
@ =========================================================
ArktosMap_EventScript_DarknessBlock::
    checkitem ITEM_FLASH_TOOL, 1
    compare VAR_RESULT, TRUE
    goto_if_eq ArktosMap_DarknessBlock_End

    lockall
    msgbox ArktosMap_Text_DarknessBlock, MSGBOX_DEFAULT
    closemessage

    applymovement LOCALID_PLAYER, ArktosMap_Movement_PushRight2
    waitmovement 0

    releaseall
    end

ArktosMap_DarknessBlock_End::
    end


@ =========================================================
@ Arktos encounter
@ =========================================================
ArktosMap_EventScript_Articuno::
    lock
    faceplayer

    @ Falls schon gefangen
    goto_if_set FLAG_ARKTOS_CAUGHT, ArktosMap_Articuno_End

    msgbox ArktosMap_Text_ArticunoCry, MSGBOX_DEFAULT
    playmoncry SPECIES_ARTICUNO, CRY_MODE_ENCOUNTER
    delay 40
    waitmoncry

    setwildbattle SPECIES_ARTICUNO, ARTICUNO_LEVEL
    special BattleSetup_StartLegendaryBattle
    waitstate
    specialvar VAR_RESULT, GetBattleOutcome

    @ Nur bei erfolgreichem Fang verschwindet Arktos dauerhaft
    compare VAR_RESULT, B_OUTCOME_CAUGHT
    goto_if_eq ArktosMap_Articuno_Caught

ArktosMap_Articuno_End:
    release
    end

ArktosMap_Articuno_Caught:
    setflag FLAG_ARKTOS_CAUGHT
    removeobject LOCALID_ARKTOS
    release
    end


@ =========================================================
@ Movements
@ =========================================================
ArktosMap_Movement_PushRight2:
    walk_right
    walk_right
    step_end


@ =========================================================
@ Text
@ =========================================================
ArktosMap_Text_DarknessBlock:
    .string "It's pitch black in that direction.\n"
    .string "I'm not going any further without\p"
    .string "a flashlight.$"

ArktosMap_Text_ArticunoCry:
    .string "Gyaoo!$"

