LuTunnel_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LuTunnel_OnTransition
	.byte 0

	.equ LUTUNNEL_KABUTOPS_LEVEL, 50


@ =========================================================
@ Beim Betreten des Tunnels
@ =========================================================
LuTunnel_OnTransition::
	setflag FLAG_LUTUNNEL_BETRETEN
	end


@ =========================================================
@ Kabutops encounter
@ =========================================================
LuTunnel_EventScript_Kabutops::
	lock
	faceplayer

	goto_if_set FLAG_LUTUNNEL_KABUTOPS_CAUGHT, LuTunnel_Kabutops_End

	msgbox LuTunnel_Text_KabutopsCry, MSGBOX_DEFAULT
	playmoncry SPECIES_KABUTOPS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry

	setwildbattle SPECIES_KABUTOPS, LUTUNNEL_KABUTOPS_LEVEL
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome

	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq LuTunnel_Kabutops_Caught

LuTunnel_Kabutops_End:
	release
	end

LuTunnel_Kabutops_Caught:
	setflag FLAG_LUTUNNEL_KABUTOPS_CAUGHT
	removeobject LOCALID_KABUTOPS_WALK
	release
	end


@ =========================================================
@ Jaw Fossil
@ =========================================================
LuTunnel_EventScript_JawFossil::
	lock
	faceplayer

	goto_if_set FLAG_LUTUNNEL_JAW_FOSSIL_TAKEN, LuTunnel_JawFossil_AlreadyTaken

	msgbox LuTunnel_Text_JawFossilFound, MSGBOX_DEFAULT
	giveitem ITEM_JAW_FOSSIL, 1
	compare VAR_RESULT, FALSE
	goto_if_eq LuTunnel_JawFossil_BagFull

	setflag FLAG_LUTUNNEL_JAW_FOSSIL_TAKEN
	removeobject LOCALID_JAW_FOSSIL
	release
	end

LuTunnel_JawFossil_BagFull:
	msgbox LuTunnel_Text_BagFull, MSGBOX_DEFAULT
	release
	end

LuTunnel_JawFossil_AlreadyTaken:
	release
	end


@ =========================================================
@ Helix Fossil
@ =========================================================
LuTunnel_EventScript_HelixFossil::
	lock
	faceplayer

	goto_if_set FLAG_LUTUNNEL_HELIX_FOSSIL_TAKEN, LuTunnel_HelixFossil_AlreadyTaken

	msgbox LuTunnel_Text_HelixFossilFound, MSGBOX_DEFAULT
	giveitem ITEM_HELIX_FOSSIL, 1
	compare VAR_RESULT, FALSE
	goto_if_eq LuTunnel_HelixFossil_BagFull

	setflag FLAG_LUTUNNEL_HELIX_FOSSIL_TAKEN
	removeobject LOCALID_HELIX_FOSSIL
	release
	end

LuTunnel_HelixFossil_BagFull:
	msgbox LuTunnel_Text_BagFull, MSGBOX_DEFAULT
	release
	end

LuTunnel_HelixFossil_AlreadyTaken:
	release
	end


@ =========================================================
@ Text
@ =========================================================
LuTunnel_Text_KabutopsCry:
	.string "Screeee!$"

LuTunnel_Text_JawFossilFound:
	.string "You found a JAW FOSSIL!$"

LuTunnel_Text_HelixFossilFound:
	.string "You found a HELIX FOSSIL!$"

LuTunnel_Text_BagFull:
	.string "Your BAG is full.$"

