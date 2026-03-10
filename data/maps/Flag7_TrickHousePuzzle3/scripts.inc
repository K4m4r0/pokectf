Flag7_TrickHousePuzzle3_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Flag7_TrickHousePuzzle3_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Flag7_TrickHousePuzzle3_OnTransition
	.byte 0

Flag7_TrickHousePuzzle3_OnResume:
	call Flag7_TrickHousePuzzle3_EventScript_UpdateButtonMetatiles
	call_if_eq VAR_TEMP_9, 0, Flag7_TrickHousePuzzle3_EventScript_SetDoorsState0
	call_if_eq VAR_TEMP_9, 1, Flag7_TrickHousePuzzle3_EventScript_SetDoorsState1
	end

Flag7_TrickHousePuzzle3_OnTransition:
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_4, 0
	setvar VAR_TEMP_8, 0
	setvar VAR_TEMP_9, 0
	end

Flag7_TrickHousePuzzle3_EventScript_UpdateButtonMetatiles::
	setmetatile 4, 14, METATILE_TrickHousePuzzle_Button_Up, FALSE
	setmetatile 3, 11, METATILE_TrickHousePuzzle_Button_Up, FALSE
	setmetatile 12, 5, METATILE_TrickHousePuzzle_Button_Up, FALSE
	setmetatile 8, 2, METATILE_TrickHousePuzzle_Button_Up, FALSE
	call_if_eq VAR_TEMP_8, 1, Flag7_TrickHousePuzzle3_EventScript_PressedButton1Metatile
	call_if_eq VAR_TEMP_8, 2, Flag7_TrickHousePuzzle3_EventScript_PressedButton2Metatile
	call_if_eq VAR_TEMP_8, 3, Flag7_TrickHousePuzzle3_EventScript_PressedButton3Metatile
	call_if_eq VAR_TEMP_8, 4, Flag7_TrickHousePuzzle3_EventScript_PressedButton4Metatile
	return

Flag7_TrickHousePuzzle3_EventScript_PressedButton1Metatile::
	setmetatile 4, 14, METATILE_TrickHousePuzzle_Button_Pressed, FALSE
	return

Flag7_TrickHousePuzzle3_EventScript_PressedButton2Metatile::
	setmetatile 3, 11, METATILE_TrickHousePuzzle_Button_Pressed, FALSE
	return

Flag7_TrickHousePuzzle3_EventScript_PressedButton3Metatile::
	setmetatile 12, 5, METATILE_TrickHousePuzzle_Button_Pressed, FALSE
	return

Flag7_TrickHousePuzzle3_EventScript_PressedButton4Metatile::
	setmetatile 8, 2, METATILE_TrickHousePuzzle_Button_Pressed, FALSE
	return

Flag7_TrickHousePuzzle3_EventScript_SetDoorsState0::
	setmetatile 1, 6, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile0, FALSE
	setmetatile 2, 6, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile1, FALSE
	setmetatile 1, 7, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile2, FALSE
	setmetatile 2, 7, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile3, FALSE
	setmetatile 1, 9, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile0, FALSE
	setmetatile 2, 9, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile1, FALSE
	setmetatile 1, 10, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile2, FALSE
	setmetatile 2, 10, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile3, FALSE
	setmetatile 4, 15, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile0, FALSE
	setmetatile 5, 15, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile1, FALSE
	setmetatile 4, 16, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile2, FALSE
	setmetatile 5, 16, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile3, FALSE
	setmetatile 13, 9, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile0, FALSE
	setmetatile 14, 9, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile1, FALSE
	setmetatile 13, 10, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile2, FALSE
	setmetatile 14, 10, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile3, FALSE
	setmetatile 13, 15, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile0, FALSE
	setmetatile 14, 15, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile1, FALSE
	setmetatile 13, 16, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile2, FALSE
	setmetatile 14, 16, METATILE_TrickHousePuzzle_BlueDoorH_Open_Tile3, FALSE
	setmetatile 3, 7, METATILE_TrickHousePuzzle_BlueDoorV_Retracted, TRUE
	setmetatile 3, 8, METATILE_TrickHousePuzzle_Floor_ShadowTop, FALSE
	setmetatile 3, 13, METATILE_TrickHousePuzzle_BlueDoorV_Retracted, TRUE
	setmetatile 3, 14, METATILE_TrickHousePuzzle_Floor_ShadowTop, FALSE
	setmetatile 6, 4, METATILE_TrickHousePuzzle_BlueDoorV_Retracted, TRUE
	setmetatile 6, 5, METATILE_TrickHousePuzzle_Floor_ShadowTop, FALSE
	setmetatile 9, 16, METATILE_TrickHousePuzzle_BlueDoorV_Retracted, TRUE
	setmetatile 9, 17, METATILE_TrickHousePuzzle_Floor_ShadowTop, FALSE
	setmetatile 12, 7, METATILE_TrickHousePuzzle_BlueDoorV_Retracted, TRUE
	setmetatile 12, 8, METATILE_TrickHousePuzzle_Floor_ShadowTop, FALSE
	setmetatile 1, 3, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile0, FALSE
	setmetatile 2, 3, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile1, FALSE
	setmetatile 1, 4, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile2, TRUE
	setmetatile 2, 4, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile3, TRUE
	setmetatile 1, 12, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile0, FALSE
	setmetatile 2, 12, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile1, FALSE
	setmetatile 1, 13, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile2, TRUE
	setmetatile 2, 13, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile3, TRUE
	setmetatile 4, 6, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile0, FALSE
	setmetatile 5, 6, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile1, FALSE
	setmetatile 4, 7, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile2, TRUE
	setmetatile 5, 7, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile3, TRUE
	setmetatile 4, 12, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile0, FALSE
	setmetatile 5, 12, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile1, FALSE
	setmetatile 4, 13, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile2, TRUE
	setmetatile 5, 13, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile3, TRUE
	setmetatile 4, 18, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile0, FALSE
	setmetatile 5, 18, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile1, FALSE
	setmetatile 4, 19, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile2, TRUE
	setmetatile 5, 19, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile3, TRUE
	setmetatile 7, 9, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile0, FALSE
	setmetatile 8, 9, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile1, FALSE
	setmetatile 7, 10, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile2, TRUE
	setmetatile 8, 10, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile3, TRUE
	setmetatile 10, 6, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile0, FALSE
	setmetatile 11, 6, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile1, FALSE
	setmetatile 10, 7, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile2, TRUE
	setmetatile 11, 7, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile3, TRUE
	setmetatile 10, 12, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile0, FALSE
	setmetatile 11, 12, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile1, FALSE
	setmetatile 10, 13, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile2, TRUE
	setmetatile 11, 13, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile3, TRUE
	setmetatile 10, 18, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile0, FALSE
	setmetatile 11, 18, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile1, FALSE
	setmetatile 10, 19, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile2, TRUE
	setmetatile 11, 19, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile3, TRUE
	setmetatile 13, 3, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile0, FALSE
	setmetatile 14, 3, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile1, FALSE
	setmetatile 13, 4, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile2, TRUE
	setmetatile 14, 4, METATILE_TrickHousePuzzle_RedDoorH_Closed_Tile3, TRUE
	setmetatile 3, 16, METATILE_TrickHousePuzzle_RedDoorV_Open0, TRUE
	setmetatile 3, 17, METATILE_TrickHousePuzzle_RedDoorV_Open1, TRUE
	setmetatile 9, 4, METATILE_TrickHousePuzzle_RedDoorV_Open0, TRUE
	setmetatile 9, 5, METATILE_TrickHousePuzzle_RedDoorV_Open1, TRUE
	return

Flag7_TrickHousePuzzle3_EventScript_SetDoorsState1::
	setmetatile 1, 6, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile0, FALSE
	setmetatile 2, 6, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile1, FALSE
	setmetatile 1, 7, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile2, TRUE
	setmetatile 2, 7, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile3, TRUE
	setmetatile 1, 9, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile0, FALSE
	setmetatile 2, 9, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile1, FALSE
	setmetatile 1, 10, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile2, TRUE
	setmetatile 2, 10, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile3, TRUE
	setmetatile 4, 15, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile0, FALSE
	setmetatile 5, 15, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile1, FALSE
	setmetatile 4, 16, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile2, TRUE
	setmetatile 5, 16, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile3, TRUE
	setmetatile 13, 9, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile0, FALSE
	setmetatile 14, 9, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile1, FALSE
	setmetatile 13, 10, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile2, TRUE
	setmetatile 14, 10, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile3, TRUE
	setmetatile 13, 15, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile0, FALSE
	setmetatile 14, 15, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile1, FALSE
	setmetatile 13, 16, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile2, TRUE
	setmetatile 14, 16, METATILE_TrickHousePuzzle_BlueDoorH_Closed_Tile3, TRUE
	setmetatile 3, 7, METATILE_TrickHousePuzzle_BlueDoorV_Open0, TRUE
	setmetatile 3, 8, METATILE_TrickHousePuzzle_BlueDoorV_Open1, TRUE
	setmetatile 3, 13, METATILE_TrickHousePuzzle_BlueDoorV_Open0, TRUE
	setmetatile 3, 14, METATILE_TrickHousePuzzle_BlueDoorV_Open1, TRUE
	setmetatile 6, 4, METATILE_TrickHousePuzzle_BlueDoorV_Open0, TRUE
	setmetatile 6, 5, METATILE_TrickHousePuzzle_BlueDoorV_Open1, TRUE
	setmetatile 9, 16, METATILE_TrickHousePuzzle_BlueDoorV_Open0, TRUE
	setmetatile 9, 17, METATILE_TrickHousePuzzle_BlueDoorV_Open1, TRUE
	setmetatile 12, 7, METATILE_TrickHousePuzzle_BlueDoorV_Open0, TRUE
	setmetatile 12, 8, METATILE_TrickHousePuzzle_BlueDoorV_Open1, TRUE
	setmetatile 1, 3, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile0, FALSE
	setmetatile 2, 3, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile1, FALSE
	setmetatile 1, 4, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile2, FALSE
	setmetatile 2, 4, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile3, FALSE
	setmetatile 1, 12, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile0, FALSE
	setmetatile 2, 12, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile1, FALSE
	setmetatile 1, 13, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile2, FALSE
	setmetatile 2, 13, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile3, FALSE
	setmetatile 4, 6, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile0, FALSE
	setmetatile 5, 6, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile1, FALSE
	setmetatile 4, 7, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile2, FALSE
	setmetatile 5, 7, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile3, FALSE
	setmetatile 4, 12, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile0, FALSE
	setmetatile 5, 12, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile1, FALSE
	setmetatile 4, 13, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile2, FALSE
	setmetatile 5, 13, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile3, FALSE
	setmetatile 4, 18, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile0, FALSE
	setmetatile 5, 18, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile1, FALSE
	setmetatile 4, 19, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile2, FALSE
	setmetatile 5, 19, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile3, FALSE
	setmetatile 7, 9, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile0, FALSE
	setmetatile 8, 9, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile1, FALSE
	setmetatile 7, 10, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile2, FALSE
	setmetatile 8, 10, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile3, FALSE
	setmetatile 10, 6, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile0, FALSE
	setmetatile 11, 6, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile1, FALSE
	setmetatile 10, 7, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile2, FALSE
	setmetatile 11, 7, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile3, FALSE
	setmetatile 10, 12, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile0, FALSE
	setmetatile 11, 12, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile1, FALSE
	setmetatile 10, 13, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile2, FALSE
	setmetatile 11, 13, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile3, FALSE
	setmetatile 10, 18, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile0, FALSE
	setmetatile 11, 18, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile1, FALSE
	setmetatile 10, 19, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile2, FALSE
	setmetatile 11, 19, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile3, FALSE
	setmetatile 13, 3, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile0, FALSE
	setmetatile 14, 3, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile1, FALSE
	setmetatile 13, 4, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile2, FALSE
	setmetatile 14, 4, METATILE_TrickHousePuzzle_RedDoorH_Open_Tile3, FALSE
	setmetatile 3, 16, METATILE_TrickHousePuzzle_RedDoorV_Retracted, TRUE
	setmetatile 3, 17, METATILE_TrickHousePuzzle_Floor_ShadowTop_Alt, FALSE
	setmetatile 9, 4, METATILE_TrickHousePuzzle_RedDoorV_Retracted, TRUE
	setmetatile 9, 5, METATILE_TrickHousePuzzle_Floor_ShadowTop_Alt, FALSE
	return

Flag7_TrickHousePuzzle3_EventScript_Button1::
	lockall
	setvar VAR_TEMP_8, 1
	goto Flag7_TrickHousePuzzle3_EventScript_PressButton
	end

Flag7_TrickHousePuzzle3_EventScript_Button2::
	lockall
	setvar VAR_TEMP_8, 2
	goto Flag7_TrickHousePuzzle3_EventScript_PressButton
	end

Flag7_TrickHousePuzzle3_EventScript_Button3::
	lockall
	setvar VAR_TEMP_8, 3
	goto Flag7_TrickHousePuzzle3_EventScript_PressButton
	end

Flag7_TrickHousePuzzle3_EventScript_Button4::
	lockall
	setvar VAR_TEMP_8, 4
	goto Flag7_TrickHousePuzzle3_EventScript_PressButton
	end

Flag7_TrickHousePuzzle3_EventScript_PressButton::
	call Flag7_TrickHousePuzzle3_EventScript_SetButton
	playse SE_PIN
	call Flag7_TrickHousePuzzle3_EventScript_UpdateButtonMetatiles
	goto Flag7_TrickHousePuzzle3_EventScript_AlternateDoors
	end

Flag7_TrickHousePuzzle3_EventScript_SetButton::
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_4, 0
	call_if_eq VAR_TEMP_8, 1, Flag7_TrickHousePuzzle3_EventScript_SetButton1
	call_if_eq VAR_TEMP_8, 2, Flag7_TrickHousePuzzle3_EventScript_SetButton2
	call_if_eq VAR_TEMP_8, 3, Flag7_TrickHousePuzzle3_EventScript_SetButton3
	call_if_eq VAR_TEMP_8, 4, Flag7_TrickHousePuzzle3_EventScript_SetButton4
	return

Flag7_TrickHousePuzzle3_EventScript_SetButton1::
	setvar VAR_TEMP_1, 1
	return

Flag7_TrickHousePuzzle3_EventScript_SetButton2::
	setvar VAR_TEMP_2, 1
	return

Flag7_TrickHousePuzzle3_EventScript_SetButton3::
	setvar VAR_TEMP_3, 1
	return

Flag7_TrickHousePuzzle3_EventScript_SetButton4::
	setvar VAR_TEMP_4, 1
	return

Flag7_TrickHousePuzzle3_EventScript_AlternateDoors::
	call_if_eq VAR_TEMP_9, 1, Flag7_TrickHousePuzzle3_EventScript_SetDoorsState0
	call_if_eq VAR_TEMP_9, 0, Flag7_TrickHousePuzzle3_EventScript_SetDoorsState1
	special DrawWholeMapView
	goto_if_eq VAR_TEMP_9, 1, Flag7_TrickHousePuzzle3_EventScript_ClearAltDoorState
	goto_if_eq VAR_TEMP_9, 0, Flag7_TrickHousePuzzle3_EventScript_SetAltDoorState
	end

Flag7_TrickHousePuzzle3_EventScript_ClearAltDoorState::
	setvar VAR_TEMP_9, 0
	releaseall
	end

Flag7_TrickHousePuzzle3_EventScript_SetAltDoorState::
	setvar VAR_TEMP_9, 1
	releaseall
	end

Flag7_TrickHousePuzzle3_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_3_STATE, 0, Flag7_TrickHousePuzzle3_EventScript_FoundScroll
	goto Flag7_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Flag7_TrickHousePuzzle3_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_3_STATE, 1
	goto Flag7_TrickHousePuzzle_EventScript_FoundScroll
	end

Flag7_TrickHousePuzzle3_EventScript_Justin::
	trainerbattle_single TRAINER_JUSTIN, Flag7_TrickHousePuzzle3_Text_JustinIntro, Flag7_TrickHousePuzzle3_Text_JustinDefeat
	msgbox Flag7_TrickHousePuzzle3_Text_JustinPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle3_EventScript_Martha::
	trainerbattle_single TRAINER_MARTHA, Flag7_TrickHousePuzzle3_Text_MarthaIntro, Flag7_TrickHousePuzzle3_Text_MarthaDefeat
	msgbox Flag7_TrickHousePuzzle3_Text_MarthaPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle3_EventScript_Alan::
	trainerbattle_single TRAINER_ALAN, Flag7_TrickHousePuzzle3_Text_AlanIntro, Flag7_TrickHousePuzzle3_Text_AlanDefeat
	msgbox Flag7_TrickHousePuzzle3_Text_AlanPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle3_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} wrote down the secret code\n"
	.string "on the door.\p"
	.string "“TRICK MASTER is coveted.”\n"
	.string "… … … … … … … …\p"
	.string "The lock clicked open!$"

Flag7_TrickHousePuzzle3_Text_JustinIntro:
	.string "I keep coming back to this same place!$"

Flag7_TrickHousePuzzle3_Text_JustinDefeat:
	.string "I'm already having trouble, and then\n"
	.string "you have to beat me? It's not fair!$"

Flag7_TrickHousePuzzle3_Text_JustinPostBattle:
	.string "It's full of doors here!\n"
	.string "It's too small and dark in here! Help!$"

Flag7_TrickHousePuzzle3_Text_MarthaIntro:
	.string "I don't know what's going on here.\n"
	.string "I'm starting to feel sad…$"

Flag7_TrickHousePuzzle3_Text_MarthaDefeat:
	.string "You… You're awful!$"

Flag7_TrickHousePuzzle3_Text_MarthaPostBattle:
	.string "I know I'm weak!\n"
	.string "And, I have no sense of direction!$"

Flag7_TrickHousePuzzle3_Text_AlanIntro:
	.string "I don't get it. What would anyone want\n"
	.string "with a house this bizarre?$"

Flag7_TrickHousePuzzle3_Text_AlanDefeat:
	.string "I don't get it.\n"
	.string "How did I lose?$"

Flag7_TrickHousePuzzle3_Text_AlanPostBattle:
	.string "I don't get it.\n"
	.string "How many traps are in this house?\p"
	.string "You may be the one to solve that.$"

