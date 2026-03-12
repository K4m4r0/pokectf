WayToCaferteria_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WayToCaferteria_OnTransition
	map_script MAP_SCRIPT_ON_DIVE_WARP, WayToCaferteria_OnDiveWarp
	.byte 0

WayToCaferteria_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	setvar VAR_TEMP_1, 0
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

WayToCaferteria_EventScript_Rival::
	end

WayToCaferteria_EventScript_RivalTrigger::
	goto_if_set FLAG_CTF_RIVAL_MARKET_DONE, WayToCaferteria_EventScript_RivalTriggerDone
	setvar VAR_TEMP_1, 1
	lockall
	call Common_EventScript_SetupRivalGfxId
	applymovement LOCAL_ID_RIVAL, WayToCaferteria_Movement_RivalApproach
	waitmovement 0
	turnobject LOCAL_ID_RIVAL, DIR_SOUTH
	turnobject LOCALID_PLAYER, DIR_NORTH
	call WayToCaferteria_EventScript_RivalBattleCommon
	releaseall
	end

WayToCaferteria_EventScript_RivalTriggerDone::
	end

WayToCaferteria_EventScript_RivalBattleCommon::
	trainerbattle_single TRAINER_LEAF, WayToCaferteria_Text_RivalIntro, WayToCaferteria_Text_RivalDefeat
	msgbox WayToCaferteria_Text_RivalPostBattle, MSGBOX_DEFAULT
	setflag FLAG_CTF_RIVAL_MARKET_DONE
	applymovement LOCAL_ID_RIVAL, WayToCaferteria_Movement_RivalRetreat
	waitmovement 0
	removeobject LOCAL_ID_RIVAL
	setvar VAR_TEMP_1, 0
	return

WayToCaferteria_EventScript_DiveLugia::
	goto EventScript_UseDive

WayToCaferteria_OnDiveWarp:
	getplayerxy VAR_0x8004, VAR_0x8005
	call WayToCaferteria_EventScript_SetDiveWarpToLugia
	end

WayToCaferteria_EventScript_SetDiveWarpToLugia::
	compare VAR_0x8004, 61
	goto_if_eq WayToCaferteria_EventScript_SetDiveWarpX61
	compare VAR_0x8004, 62
	goto_if_eq WayToCaferteria_EventScript_SetDiveWarpX62
	return

WayToCaferteria_EventScript_SetDiveWarpX61::
	compare VAR_0x8005, 14
	goto_if_eq WayToCaferteria_EventScript_SetDiveWarpSurfTL
	compare VAR_0x8005, 15
	goto_if_eq WayToCaferteria_EventScript_SetDiveWarpSurfBL
	return

WayToCaferteria_EventScript_SetDiveWarpX62::
	compare VAR_0x8005, 14
	goto_if_eq WayToCaferteria_EventScript_SetDiveWarpSurfTR
	compare VAR_0x8005, 15
	goto_if_eq WayToCaferteria_EventScript_SetDiveWarpSurfBR
	return

WayToCaferteria_EventScript_SetDiveWarpSurfTL::
	setdivewarp MAP_LUGIA_SPAWN, 10, 32
	return

WayToCaferteria_EventScript_SetDiveWarpSurfBL::
	setdivewarp MAP_LUGIA_SPAWN, 10, 33
	return

WayToCaferteria_EventScript_SetDiveWarpSurfTR::
	setdivewarp MAP_LUGIA_SPAWN, 11, 32
	return

WayToCaferteria_EventScript_SetDiveWarpSurfBR::
	setdivewarp MAP_LUGIA_SPAWN, 11, 33
	return

WayToCaferteria_EventScript_DeepForestLakeSign::
	msgbox WayToCaferteria_Text_DeepForestLake, MSGBOX_SIGN
	end

WayToCaferteria_EventScript_EconSign::
	msgbox WayToCaferteria_Text_EconSign, MSGBOX_SIGN
	end

WayToCaferteria_Text_DeepForestLake:
	.string "Deep Forest Lake$"

WayToCaferteria_Text_EconSign:
	.string "Department of Economics\p"
	.string "Field Study Area\l"
	.string "Please ignore the students\n"
	.string "practicing 'market competition'.$"

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
	.string "Rich Boy: What?!\p"
	.string "Do you know how much\n"
	.string "my Porsche costs?$"

WayToCaferteria_Text_PorscheBoyAfterBattleRepeat:
	.string "Rich Boy: Lane's clear... for now.$"

WayToCaferteria_Text_RivalIntro:
	.string "TRAINER.\p"
	.string "I was wondering when you'd show up.\p"
	.string "While you were busy digging\n"
	.string "beneath systems...\p"
	.string "I focused on something\n"
	.string "much more important.\p"
	.string "Value.\p"
	.string "You see, in business it's not about\n"
	.string "understanding every detail.\p"
	.string "It's about knowing what actually\n"
	.string "matters.\p"
	.string "Strategy.\n"
	.string "Influence.\n"
	.string "Capital.\p"
	.string "And POKéMON battles\n"
	.string "are just another market.\p"
	.string "Supply.\n"
	.string "Demand.\n"
	.string "Competition.\p"
	.string "Let's see whose strategy\n"
	.string "has the better return.$"

WayToCaferteria_Text_RivalDefeat:
	.string "So you broke through\n"
	.string "my strategy.\p"
	.string "Interesting.\p"
	.string "Maybe the market isn't always\n"
	.string "predictable.\p"
	.string "Or maybe...\p"
	.string "you simply refuse\n"
	.string "to play by the rules.$"

WayToCaferteria_Text_RivalPostBattle:
	.string "Either way.\p"
	.string "The legendary POKéMON\n"
	.string "is waiting ahead.\p"
	.string "Go on.\p"
	.string "But remember something.\p"
	.string "Even the deepest system\n"
	.string "still runs on resources.\p"
	.string "And someone always\n"
	.string "controls the market.$"

WayToCaferteria_Movement_RivalRetreat:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

WayToCaferteria_Movement_RivalApproach:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end
