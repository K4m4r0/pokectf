WayToCaferteria_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WayToCaferteria_OnTransition
	.byte 0

WayToCaferteria_OnTransition:
	call WayToCaferteria_EventScript_HandlePorscheBoyState
	end

WayToCaferteria_EventScript_HandlePorscheBoyState::
	goto_if_set FLAG_CTF_RYBBEL_CLASS_DONE, WayToCaferteria_EventScript_MovePorscheBoy
	return

WayToCaferteria_EventScript_MovePorscheBoy::
	setobjectxyperm LOCAL_ID_PORSCHEBOY, 33, 14
	return

WayToCaferteria_EventScript_PorscheBoy::
	lock
	faceplayer
	goto_if_set FLAG_CTF_RYBBEL_CLASS_DONE, WayToCaferteria_EventScript_PorscheBoyChallenge
	msgbox WayToCaferteria_Text_BusinessStudent, MSGBOX_DEFAULT
	release
	end

WayToCaferteria_EventScript_PorscheBoyChallenge::
	call WayToCaferteria_EventScript_PorscheBoyBattleCommon
	release
	end

WayToCaferteria_EventScript_PorscheBoyTrigger::
	goto_if_set FLAG_CTF_RYBBEL_CLASS_DONE, WayToCaferteria_EventScript_PorscheBoyTriggerActive
	end

WayToCaferteria_EventScript_PorscheBoyTriggerActive::
	lockall
	turnobject LOCAL_ID_PORSCHEBOY, DIR_SOUTH
	turnobject LOCALID_PLAYER, DIR_NORTH
	call WayToCaferteria_EventScript_PorscheBoyBattleCommon
	releaseall
	end

WayToCaferteria_EventScript_PorscheBoyBattleCommon::
	checktrainerflag TRAINER_PORSCHE_BOY
	goto_if_eq VAR_RESULT, 1, WayToCaferteria_EventScript_PorscheBoyAfterBattleRepeat
	trainerbattle_single TRAINER_PORSCHE_BOY, WayToCaferteria_Text_PorscheBoyIntro, WayToCaferteria_Text_PorscheBoyDefeat
	msgbox WayToCaferteria_Text_PorscheBoyPostBattle, MSGBOX_DEFAULT
	return

WayToCaferteria_EventScript_PorscheBoyAfterBattleRepeat::
	msgbox WayToCaferteria_Text_PorscheBoyAfterBattleRepeat, MSGBOX_DEFAULT
	return

WayToCaferteria_EventScript_DeepForestLakeSign::
	msgbox WayToCaferteria_Text_DeepForestLake, MSGBOX_SIGN
	end

WayToCaferteria_Text_DeepForestLake:
	.string "Deep Forest Lake$"

WayToCaferteria_Text_BusinessStudent:
	.string "Stop. I'm a Business Informatics major, okay?\n"
	.string "And my dad still won't buy me a Porsche.\p"
	.string "Says I have to 'earn it.'\n"
	.string "Unbelievable. Nobody passes.$"

WayToCaferteria_Text_PorscheBoyIntro:
	.string "Rich Boy: I got my Porsche anyway.\p"
	.string "Sold some Bitcoin, haha.\n"
	.string "Now I'm going to drive over you!$"

WayToCaferteria_Text_PorscheBoyDefeat:
	.string "Rich Boy: Whoa!\p"
	.string "I stalled out.$"

WayToCaferteria_Text_PorscheBoyPostBattle:
	.string "Rich Boy: Fine, go through.\p"
	.string "I'll just rev in neutral.$"

WayToCaferteria_Text_PorscheBoyAfterBattleRepeat:
	.string "Rich Boy: Lane's clear... for now.$"
