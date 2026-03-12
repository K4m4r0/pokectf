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

Flag7_TrickHousePuzzle4_EventScript_Worker::
	trainerbattle_single TRAINER_YUJI, Flag7_TrickHousePuzzle4_Text_WorkerIntro, Flag7_TrickHousePuzzle4_Text_WorkerDefeat
	msgbox Flag7_TrickHousePuzzle4_Text_WorkerPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle4_EventScript_Researcher::
	trainerbattle_single TRAINER_CORA, Flag7_TrickHousePuzzle4_Text_ResearcherIntro, Flag7_TrickHousePuzzle4_Text_ResearcherDefeat
	msgbox Flag7_TrickHousePuzzle4_Text_ResearcherPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle4_EventScript_TunnelDweller::
	trainerbattle_single TRAINER_PAULA, Flag7_TrickHousePuzzle4_Text_DwellerIntro, Flag7_TrickHousePuzzle4_Text_DwellerDefeat
	msgbox Flag7_TrickHousePuzzle4_Text_DwellerPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle4_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} wrote down the secret code\n"
	.string "on the door.\p"
	.string "“TRICK MASTER is cool.”\n"
	.string "… … … … … … … …\p"
	.string "The lock clicked open!$"

Flag7_TrickHousePuzzle4_Text_WorkerIntro:
	.string "Hm? A student?\p"
	.string "Haven't seen one down here\n"
	.string "in quite some time.\p"
	.string "Most people turn around\n"
	.string "after the first few tunnels.\p"
	.string "But if you're still walking...\p"
	.string "you must be looking for something deeper.$"

Flag7_TrickHousePuzzle4_Text_WorkerDefeat:
	.string "Heh...\n"
	.string "Guess the next generation's tough.$"

Flag7_TrickHousePuzzle4_Text_WorkerPostBattle:
	.string "You're cleared to head deeper.\n"
	.string "Watch your step down there.$"

Flag7_TrickHousePuzzle4_Text_ResearcherIntro:
	.string "Oh... someone finally found this lab.\p"
	.string "I moved my research down here\n"
	.string "years ago.\p"
	.string "No distractions. No administrators.\p"
	.string "Just data... and POKéMON.$"

Flag7_TrickHousePuzzle4_Text_ResearcherDefeat:
	.string "Fascinating...$"

Flag7_TrickHousePuzzle4_Text_ResearcherPostBattle:
	.string "Your battle strategy was surprisingly\n"
	.string "efficient. Consider me impressed.$"

Flag7_TrickHousePuzzle4_Text_DwellerIntro:
	.string "You're getting close.\p"
	.string "Most people never reach\n"
	.string "this far beneath the campus.\p"
	.string "The tunnels go deeper still...\p"
	.string "But only strong trainers make it past me.$"

Flag7_TrickHousePuzzle4_Text_DwellerDefeat:
	.string "Not bad.$"

Flag7_TrickHousePuzzle4_Text_DwellerPostBattle:
	.string "Maybe you really are ready\n"
	.string "for what's deeper below.$"
