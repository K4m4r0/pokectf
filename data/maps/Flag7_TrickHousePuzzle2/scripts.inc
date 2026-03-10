Flag7_TrickHousePuzzle2_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Flag7_TrickHousePuzzle2_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Flag7_TrickHousePuzzle2_OnTransition
	.byte 0

Flag7_TrickHousePuzzle2_OnResume:
	call_if_eq VAR_TEMP_1, 1, Flag7_TrickHousePuzzle2_EventScript_PressButton1
	call_if_eq VAR_TEMP_2, 1, Flag7_TrickHousePuzzle2_EventScript_PressButton2
	call_if_eq VAR_TEMP_3, 1, Flag7_TrickHousePuzzle2_EventScript_PressButton3
	call_if_eq VAR_TEMP_4, 1, Flag7_TrickHousePuzzle2_EventScript_PressButton4
	end

Flag7_TrickHousePuzzle2_OnTransition:
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_4, 0
	end

Flag7_TrickHousePuzzle2_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_2_STATE, 0, Flag7_TrickHousePuzzle2_EventScript_FoundScroll
	goto Flag7_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Flag7_TrickHousePuzzle2_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_2_STATE, 1
	goto Flag7_TrickHousePuzzle_EventScript_FoundScroll
	end

Flag7_TrickHousePuzzle2_EventScript_Button1::
	lockall
	setvar VAR_TEMP_1, 1
	playse SE_PIN
	call Flag7_TrickHousePuzzle2_EventScript_PressButton1
	special DrawWholeMapView
	releaseall
	end

Flag7_TrickHousePuzzle2_EventScript_Button2::
	lockall
	setvar VAR_TEMP_2, 1
	playse SE_PIN
	call Flag7_TrickHousePuzzle2_EventScript_PressButton2
	special DrawWholeMapView
	releaseall
	end

Flag7_TrickHousePuzzle2_EventScript_Button3::
	lockall
	setvar VAR_TEMP_3, 1
	playse SE_PIN
	call Flag7_TrickHousePuzzle2_EventScript_PressButton3
	special DrawWholeMapView
	releaseall
	end

Flag7_TrickHousePuzzle2_EventScript_Button4::
	lockall
	setvar VAR_TEMP_4, 1
	playse SE_PIN
	call Flag7_TrickHousePuzzle2_EventScript_PressButton4
	special DrawWholeMapView
	releaseall
	end

Flag7_TrickHousePuzzle2_EventScript_PressButton1::
	setmetatile 11, 12, METATILE_TrickHousePuzzle_Button_Pressed, FALSE
	setmetatile 1, 13, METATILE_TrickHousePuzzle_Door_Shuttered, FALSE
	return

Flag7_TrickHousePuzzle2_EventScript_PressButton2::
	setmetatile 0, 4, METATILE_TrickHousePuzzle_Button_Pressed, FALSE
	setmetatile 5, 6, METATILE_TrickHousePuzzle_Door_Shuttered, FALSE
	return

Flag7_TrickHousePuzzle2_EventScript_PressButton3::
	setmetatile 14, 5, METATILE_TrickHousePuzzle_Button_Pressed, FALSE
	setmetatile 7, 15, METATILE_TrickHousePuzzle_Door_Shuttered, FALSE
	return

Flag7_TrickHousePuzzle2_EventScript_PressButton4::
	setmetatile 7, 11, METATILE_TrickHousePuzzle_Button_Pressed, FALSE
	setmetatile 14, 12, METATILE_TrickHousePuzzle_Door_Shuttered, FALSE
	return

Flag7_TrickHousePuzzle2_EventScript_Ted::
	trainerbattle_single TRAINER_TED, Flag7_TrickHousePuzzle2_Text_TedIntro, Flag7_TrickHousePuzzle2_Text_TedDefeat
	msgbox Flag7_TrickHousePuzzle2_Text_TedPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle2_EventScript_Paul::
	trainerbattle_single TRAINER_PAUL, Flag7_TrickHousePuzzle2_Text_PaulIntro, Flag7_TrickHousePuzzle2_Text_PaulDefeat
	msgbox Flag7_TrickHousePuzzle2_Text_PaulPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle2_EventScript_Georgia::
	trainerbattle_single TRAINER_GEORGIA, Flag7_TrickHousePuzzle2_Text_GeorgiaIntro, Flag7_TrickHousePuzzle2_Text_GeorgiaDefeat
	msgbox Flag7_TrickHousePuzzle2_Text_GeorgiaPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle2_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} wrote down the secret code\n"
	.string "on the door.\p"
	.string "“TRICK MASTER is smart.”\n"
	.string "… … … … … … … …\p"
	.string "The lock clicked open!$"

Flag7_TrickHousePuzzle2_Text_TedIntro:
	.string "Which switch closes which hole?$"

Flag7_TrickHousePuzzle2_Text_TedDefeat:
	.string "After that battle, I'm even more\n"
	.string "confused!$"

Flag7_TrickHousePuzzle2_Text_TedPostBattle:
	.string "Can I get you to push all the buttons\n"
	.string "for me?$"

Flag7_TrickHousePuzzle2_Text_PaulIntro:
	.string "Oh! You're on your second TRICK HOUSE\n"
	.string "challenge!$"

Flag7_TrickHousePuzzle2_Text_PaulDefeat:
	.string "You're good at battling too?$"

Flag7_TrickHousePuzzle2_Text_PaulPostBattle:
	.string "The TRICK MASTER rigged all the tricks\n"
	.string "in this house all by himself.$"

Flag7_TrickHousePuzzle2_Text_GeorgiaIntro:
	.string "I want to make my own GYM one day.\n"
	.string "So, I'm studying how to set traps.$"

Flag7_TrickHousePuzzle2_Text_GeorgiaDefeat:
	.string "I didn't study battling enough!$"

Flag7_TrickHousePuzzle2_Text_GeorgiaPostBattle:
	.string "You're strong, aren't you?\n"
	.string "Maybe even enough to be a GYM LEADER!$"

