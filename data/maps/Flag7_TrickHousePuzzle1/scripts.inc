Flag7_TrickHousePuzzle1_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Flag7_TrickHousePuzzle1_OnLoad
	.byte 0

Flag7_TrickHousePuzzle1_OnLoad:
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_1_STATE, 2, Flag7_TrickHousePuzzle1_EventScript_OpenDoor
	end

Flag7_TrickHousePuzzle1_EventScript_OpenDoor::
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, FALSE
	end

Flag7_TrickHousePuzzle1_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_1_STATE, 0, Flag7_TrickHousePuzzle1_EventScript_FoundScroll
	goto Flag7_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Flag7_TrickHousePuzzle1_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_1_STATE, 1
	goto Flag7_TrickHousePuzzle_EventScript_FoundScroll
	end

Flag7_TrickHousePuzzle1_EventScript_Sally::
	trainerbattle_single TRAINER_SALLY, Flag7_TrickHousePuzzle1_Text_SallyIntro, Flag7_TrickHousePuzzle1_Text_SallyDefeat
	msgbox Flag7_TrickHousePuzzle1_Text_SallyPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle1_EventScript_Eddie::
	trainerbattle_single TRAINER_EDDIE, Flag7_TrickHousePuzzle1_Text_EddieIntro, Flag7_TrickHousePuzzle1_Text_EddieDefeat
	msgbox Flag7_TrickHousePuzzle1_Text_EddiePostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle1_EventScript_Robin::
	trainerbattle_single TRAINER_ROBIN, Flag7_TrickHousePuzzle1_Text_RobinIntro, Flag7_TrickHousePuzzle1_Text_RobinDefeat
	msgbox Flag7_TrickHousePuzzle1_Text_RobinPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle1_Text_WroteSecretCodeLockOpened::
	.string "{PLAYER} wrote down the secret code\n"
	.string "on the door.\p"
	.string "“TRICK MASTER is fabulous.”\n"
	.string "… … … … … … … …\p"
	.string "The lock clicked open!$"

Flag7_TrickHousePuzzle1_Text_SallyIntro:
	.string "I'll hack and slash my way to victory\n"
	.string "with the CUT we just learned!$"

Flag7_TrickHousePuzzle1_Text_SallyDefeat:
	.string "Why are you so serious?$"

Flag7_TrickHousePuzzle1_Text_SallyPostBattle:
	.string "I never get tired of hacking\n"
	.string "and slashing!$"

Flag7_TrickHousePuzzle1_Text_EddieIntro:
	.string "I wandered into this weird house\n"
	.string "by accident…$"

Flag7_TrickHousePuzzle1_Text_EddieDefeat:
	.string "And now I've lost…$"

Flag7_TrickHousePuzzle1_Text_EddiePostBattle:
	.string "I lost my way, I lost a battle, and I'm\n"
	.string "now even more lost… I can't get out…$"

Flag7_TrickHousePuzzle1_Text_RobinIntro:
	.string "Just who is the TRICK MASTER?$"

Flag7_TrickHousePuzzle1_Text_RobinDefeat:
	.string "I lost while I was lost in thought!$"

Flag7_TrickHousePuzzle1_Text_RobinPostBattle:
	.string "You're strong!\n"
	.string "Just who are you?$"

