HINTERHOF_MapScripts::
	.byte 0

@ =========================================================
@ Wildes I3C_AND
@ =========================================================
HINTERHOF_EventScript_I3CAndObject::
	lockall
	faceplayer

	goto_if_set FLAG_I3C_AND_CAUGHT, HINTERHOF_I3CAnd_End

	msgbox HINTERHOF_Text_What, MSGBOX_DEFAULT
	closemessage

	setwildbattle SPECIES_I3C_AND, 25, ITEM_SOFT_SAND
	specialvar VAR_RESULT, BattleSetup_StartLegendaryBattle
	waitstate

	@ B_OUTCOME_CAUGHT = 7
	compare VAR_RESULT, 7
	goto_if_eq HINTERHOF_I3CAnd_Caught

	releaseall
	end

HINTERHOF_I3CAnd_Caught:
	setflag FLAG_I3C_AND_CAUGHT
	removeobject LOCALID_I3C_AND_OBJ
	releaseall
	end

HINTERHOF_I3CAnd_End:
	releaseall
	end


HINTERHOF_Text_What:
	.string "This poor POKéMON was just thrown\n"
	.string "in the trash. Oh crap, it's\p"
	.string "attacking!$"

