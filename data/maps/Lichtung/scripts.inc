Lichtung_MapScripts::
    .byte 0

    .equ LICHTUNG_BULBASAUR_LEVEL, 30


@ =========================================================
@ Wildes Bulbasaur
@ =========================================================
Lichtung_EventScript_Bulbasaur::
    lockall
    faceplayer

    goto_if_set FLAG_LICHTUNG_BULBASAUR_CAUGHT, Lichtung_Bulbasaur_End

    msgbox Lichtung_Text_BulbasaurCry, MSGBOX_DEFAULT
    closemessage

    setwildbattle SPECIES_BULBASAUR, LICHTUNG_BULBASAUR_LEVEL, ITEM_NONE
    specialvar VAR_RESULT, BattleSetup_StartScriptedWildBattle
    waitstate

    @ B_OUTCOME_CAUGHT = 7
    compare VAR_RESULT, 7
    goto_if_eq Lichtung_Bulbasaur_Caught

    releaseall
    end

Lichtung_Bulbasaur_Caught:
    setflag FLAG_LICHTUNG_BULBASAUR_CAUGHT
    removeobject LOCALID_LICHTUNG_BULBASAUR
    releaseall
    end

Lichtung_Bulbasaur_End:
    releaseall
    end


@ =========================================================
@ Text
@ =========================================================
Lichtung_Text_BulbasaurCry:
    .string "Bulbasaur!$"






@ =========================================================
@ Blocker Schild
@ =========================================================

Lichtung_EventScript_Blocker::
	msgbox Lichtung_Text_Blocker, MSGBOX_SIGN
	end

Lichtung_Text_Blocker::
	.string "Unlocked after a great victory.$"
