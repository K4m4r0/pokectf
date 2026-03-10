Flag7_TrickHousePuzzle4_MapScripts::
	.byte 0

Flag7_TrickHousePuzzle4_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_4_STATE, 0, Flag7_TrickHousePuzzle4_EventScript_FoundScroll
	goto Flag7_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Flag7_TrickHousePuzzle4_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_4_STATE, 1
	goto Flag7_TrickHousePuzzle_EventScript_FoundScroll
	end

Flag7_TrickHousePuzzle4_EventScript_Cora::
	trainerbattle_single TRAINER_CORA, Flag7_TrickHousePuzzle4_Text_CoraIntro, Flag7_TrickHousePuzzle4_Text_CoraDefeat
	msgbox Flag7_TrickHousePuzzle4_Text_CoraPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle4_EventScript_Yuji::
	trainerbattle_single TRAINER_YUJI, Flag7_TrickHousePuzzle4_Text_YujiIntro, Flag7_TrickHousePuzzle4_Text_YujiDefeat
	msgbox Flag7_TrickHousePuzzle4_Text_YujiPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle4_EventScript_Paula::
	trainerbattle_single TRAINER_PAULA, Flag7_TrickHousePuzzle4_Text_PaulaIntro, Flag7_TrickHousePuzzle4_Text_PaulaDefeat
	msgbox Flag7_TrickHousePuzzle4_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle4_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} wrote down the secret code\n"
	.string "on the door.\p"
	.string "“TRICK MASTER is cool.”\n"
	.string "… … … … … … … …\p"
	.string "The lock clicked open!$"

Flag7_TrickHousePuzzle4_Text_CoraIntro:
	.string "It's too much bother to think this out.\n"
	.string "I only wanted to battle!$"

Flag7_TrickHousePuzzle4_Text_CoraDefeat:
	.string "Even though I lost, I still like battling\n"
	.string "the best!$"

Flag7_TrickHousePuzzle4_Text_CoraPostBattle:
	.string "Wouldn't you agree? You would go\n"
	.string "anywhere if TRAINERS were there.$"

Flag7_TrickHousePuzzle4_Text_YujiIntro:
	.string "Heh! Boulders like this, I can brush\n"
	.string "aside with one finger!$"

Flag7_TrickHousePuzzle4_Text_YujiDefeat:
	.string "I can push boulders, but I can't solve\n"
	.string "the puzzle…$"

Flag7_TrickHousePuzzle4_Text_YujiPostBattle:
	.string "It's not good enough to be brawny…\n"
	.string "You have to use your head. Be brainy!$"

Flag7_TrickHousePuzzle4_Text_PaulaIntro:
	.string "The TRICK HOUSE is getting trickier,\n"
	.string "isn't it?$"

Flag7_TrickHousePuzzle4_Text_PaulaDefeat:
	.string "Aaak!$"

Flag7_TrickHousePuzzle4_Text_PaulaPostBattle:
	.string "Has anyone made it to the end?$"

