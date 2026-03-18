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
    specialvar VAR_RESULT, BattleSetup_StartLegendaryBattle
    waitstate

    @ Nur bei erfolgreichem Fang verschwindet Arktos dauerhaft
    compare VAR_RESULT, 1
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
@ Text
@ =========================================================
ArktosMap_Text_ArticunoCry:
    .string "Gyaoo!$"

