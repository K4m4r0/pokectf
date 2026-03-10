Flag7_TrickHousePuzzle6_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Flag7_TrickHousePuzzle6_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Flag7_TrickHousePuzzle6_OnWarp
	.byte 0

Flag7_TrickHousePuzzle6_OnTransition:
	special RotatingGate_InitPuzzle
	end

Flag7_TrickHousePuzzle6_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, Flag7_TrickHousePuzzle6_EventScript_InitPuzzle
	.2byte 0

@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_5
Flag7_TrickHousePuzzle6_EventScript_InitPuzzle::
	special RotatingGate_InitPuzzleAndGraphics
	end

Flag7_TrickHousePuzzle6_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_6_STATE, 0, Flag7_TrickHousePuzzle6_EventScript_FoundScroll
	goto Flag7_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Flag7_TrickHousePuzzle6_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_6_STATE, 1
	goto Flag7_TrickHousePuzzle_EventScript_FoundScroll
	end

Flag7_TrickHousePuzzle6_EventScript_Sophia::
	trainerbattle_single TRAINER_SOPHIA, Flag7_TrickHousePuzzle6_Text_SophiaIntro, Flag7_TrickHousePuzzle6_Text_SophiaDefeat
	msgbox Flag7_TrickHousePuzzle6_Text_SophiaPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle6_EventScript_Benny::
	trainerbattle_single TRAINER_BENNY, Flag7_TrickHousePuzzle6_Text_BennyIntro, Flag7_TrickHousePuzzle6_Text_BennyDefeat
	msgbox Flag7_TrickHousePuzzle6_Text_BennyPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle6_EventScript_Sebastian::
	trainerbattle_single TRAINER_SEBASTIAN, Flag7_TrickHousePuzzle6_Text_SebastianIntro, Flag7_TrickHousePuzzle6_Text_SebastianDefeat
	msgbox Flag7_TrickHousePuzzle6_Text_SebastianPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle6_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} wrote down the secret code\n"
	.string "on the door.\p"
	.string "“TRICK MASTER is my life.”\n"
	.string "… … … … … … … …\p"
	.string "The lock clicked open!$"

Flag7_TrickHousePuzzle6_Text_SophiaIntro:
	.string "When I heard there was a strange\n"
	.string "house, I had to check it out.$"

Flag7_TrickHousePuzzle6_Text_SophiaDefeat:
	.string "I've discovered a tough TRAINER!$"

Flag7_TrickHousePuzzle6_Text_SophiaPostBattle:
	.string "I'm sure having a good time checking\n"
	.string "this place out.\p"
	.string "It's a challenge I've found worth\n"
	.string "repeating!$"

Flag7_TrickHousePuzzle6_Text_BennyIntro:
	.string "Maybe I could get my BIRD POKéMON\n"
	.string "to fly over the wall…$"

Flag7_TrickHousePuzzle6_Text_BennyDefeat:
	.string "Gwaaah! I blew it!$"

Flag7_TrickHousePuzzle6_Text_BennyPostBattle:
	.string "Ehehehe… I guess I lost because\n"
	.string "I was trying to cheat.$"

Flag7_TrickHousePuzzle6_Text_SebastianIntro:
	.string "I'm getting dizzy from these rotating\n"
	.string "doors…$"

Flag7_TrickHousePuzzle6_Text_SebastianDefeat:
	.string "Everything's spinning around and\n"
	.string "around. I can't take this anymore…$"

Flag7_TrickHousePuzzle6_Text_SebastianPostBattle:
	.string "You don't seem to be affected at all.\n"
	.string "Or do you have your poker face on?$"

