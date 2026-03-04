Flag7_TrickHousePuzzle8_MapScripts::
	.byte 0

Flag7_TrickHousePuzzle8_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_8_STATE, 0, Flag7_TrickHousePuzzle8_EventScript_FoundScroll
	goto Flag7_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Flag7_TrickHousePuzzle8_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_8_STATE, 1
	goto Flag7_TrickHousePuzzle_EventScript_FoundScroll
	end

Flag7_TrickHousePuzzle8_EventScript_Vincent::
	trainerbattle_single TRAINER_VINCENT, Flag7_TrickHousePuzzle8_Text_VincentIntro, Flag7_TrickHousePuzzle8_Text_VincentDefeat
	msgbox Flag7_TrickHousePuzzle8_Text_VincentPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle8_EventScript_Keira::
	trainerbattle_single TRAINER_KEIRA, Flag7_TrickHousePuzzle8_Text_KeiraIntro, Flag7_TrickHousePuzzle8_Text_KeiraDefeat
	msgbox Flag7_TrickHousePuzzle8_Text_KeiraPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle8_EventScript_Leroy::
	trainerbattle_single TRAINER_LEROY, Flag7_TrickHousePuzzle8_Text_LeroyIntro, Flag7_TrickHousePuzzle8_Text_LeroyDefeat
	msgbox Flag7_TrickHousePuzzle8_Text_LeroyPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle8_Text_WroteSecretCodeLockOpened::
	.string "{PLAYER} wrote down the secret code\n"
	.string "on the door.\p"
	.string "“TRICK MASTER I love.”\n"
	.string "… … … … … … … …\p"
	.string "The lock clicked open!$"

Flag7_TrickHousePuzzle8_Text_VincentIntro:
	.string "Not many TRAINERS have made it\n"
	.string "this far.$"

Flag7_TrickHousePuzzle8_Text_VincentDefeat:
	.string "That must mean you're tough, too…$"

Flag7_TrickHousePuzzle8_Text_VincentPostBattle:
	.string "You've beaten the POKéMON LEAGUE\n"
	.string "CHAMPION? That's too much!$"

Flag7_TrickHousePuzzle8_Text_KeiraIntro:
	.string "Consider yourself lucky to be\n"
	.string "battling me!$"

Flag7_TrickHousePuzzle8_Text_KeiraDefeat:
	.string "This isn't right!\n"
	.string "I can't lose!$"

Flag7_TrickHousePuzzle8_Text_KeiraPostBattle:
	.string "It's a miracle that you beat me.\n"
	.string "You can brag about it.$"

Flag7_TrickHousePuzzle8_Text_LeroyIntro:
	.string "You've been slugging through the TRICK\n"
	.string "HOUSE challenge, too.$"

Flag7_TrickHousePuzzle8_Text_LeroyDefeat:
	.string "I see…\n"
	.string "You possess an extraordinary style.$"

Flag7_TrickHousePuzzle8_Text_LeroyPostBattle:
	.string "Seeing someone like you should please\n"
	.string "the TRICK MASTER.$"

