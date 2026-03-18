Neckarau_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Neckarau_OnTransition
	.byte 0

Neckarau_OnTransition::
	clearflag FLAG_LUDWIGSHAFEN_REGEN
	end


@ =========================================================
@ Wildes Squirtle
@ =========================================================
Neckarau_EventScript_Squirtle::
	lockall
	faceplayer

	goto_if_set FLAG_NECKARAU_SQUIRTLE_CAUGHT, Neckarau_Squirtle_End

	msgbox Neckarau_Text_SquirtleCry, MSGBOX_DEFAULT
	closemessage

	setwildbattle SPECIES_SQUIRTLE, 30, ITEM_EVIOLITE
	specialvar VAR_RESULT, BattleSetup_StartLegendaryBattle
	waitstate

	@ B_OUTCOME_CAUGHT = 7
	compare VAR_RESULT, 7
	goto_if_eq Neckarau_Squirtle_Caught

	releaseall
	end

Neckarau_Squirtle_Caught:
	setflag FLAG_NECKARAU_SQUIRTLE_CAUGHT
	removeobject LOCALID_NECKARAU_SQUIRTLE
	releaseall
	end

Neckarau_Squirtle_End:
	releaseall
	end


@ =========================================================
@ Sign
@ =========================================================
Neckarau_EventScript_Sign::
	msgbox Neckarau_Text_Sign, MSGBOX_SIGN
	end


@ =========================================================
@ Text
@ =========================================================
Neckarau_Text_SquirtleCry:
	.string "Squirtle!$"

Neckarau_Text_Sign:
	.string "NECKARAU\n"
	.string "a vibrant neighborhood.$"

