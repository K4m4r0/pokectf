HotSprings_MapScripts::
    .byte 0

    .equ HOTSPRINGS_CHARMANDER_LEVEL, 15


@ =========================================================
@ Wildes Charmander
@ =========================================================
HotSprings_EventScript_Charmander::
    lockall
    faceplayer

    goto_if_set FLAG_HOTSPRINGS_CHARMANDER_CAUGHT, HotSprings_Charmander_End

    msgbox HotSprings_Text_CharmanderCry, MSGBOX_DEFAULT
    closemessage

    setwildbattle SPECIES_CHARMANDER, HOTSPRINGS_CHARMANDER_LEVEL, ITEM_NONE
    specialvar VAR_RESULT, BattleSetup_StartScriptedWildBattle
    waitstate

    @ B_OUTCOME_CAUGHT = 7
    compare VAR_RESULT, 7
    goto_if_eq HotSprings_Charmander_Caught

    releaseall
    end

HotSprings_Charmander_Caught:
    setflag FLAG_HOTSPRINGS_CHARMANDER_CAUGHT
    removeobject LOCALID_HOTSPRINGS_CHARMANDER
    releaseall
    end

HotSprings_Charmander_End:
    releaseall
    end


@ =========================================================
@ Text
@ =========================================================
HotSprings_Text_CharmanderCry:
    .string "Charrr!$"

