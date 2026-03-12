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

Flag7_TrickHousePuzzle6_EventScript_Engineer::
	trainerbattle_single TRAINER_SOPHIA, Flag7_TrickHousePuzzle6_Text_EngineerIntro, Flag7_TrickHousePuzzle6_Text_EngineerDefeat
	msgbox Flag7_TrickHousePuzzle6_Text_EngineerPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle6_EventScript_TunnelResidentA::
	trainerbattle_single TRAINER_BENNY, Flag7_TrickHousePuzzle6_Text_TunnelAIntro, Flag7_TrickHousePuzzle6_Text_TunnelADefeat
	msgbox Flag7_TrickHousePuzzle6_Text_TunnelAPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle6_EventScript_TunnelResidentB::
	trainerbattle_single TRAINER_SEBASTIAN, Flag7_TrickHousePuzzle6_Text_TunnelBIntro, Flag7_TrickHousePuzzle6_Text_TunnelBDefeat
	msgbox Flag7_TrickHousePuzzle6_Text_TunnelBPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle6_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} wrote down the secret code\n"
	.string "on the door.\p"
	.string "“TRICK MASTER is my life.”\n"
	.string "… … … … … … … …\p"
	.string "The lock clicked open!$"

Flag7_TrickHousePuzzle6_Text_EngineerIntro:
	.string "You're pretty far beneath the campus now.\p"
	.string "Most people never make it past the upper\n"
	.string "maintenance halls.\p"
	.string "Down here we keep the real systems running.\n"
	.string "Power. Cooling. Infrastructure.\p"
	.string "Let's see if your POKéMON can handle\n"
	.string "real pressure.$"

Flag7_TrickHousePuzzle6_Text_EngineerDefeat:
	.string "Impressive...\n"
	.string "Your system stability is better than expected.$"

Flag7_TrickHousePuzzle6_Text_EngineerPostBattle:
	.string "Consider this checkpoint cleared.\n"
	.string "Stay alert; it gets tougher below.$"

Flag7_TrickHousePuzzle6_Text_TunnelAIntro:
	.string "Oh... another visitor.\p"
	.string "We used to work on the upper campus.\p"
	.string "But after a while... we realized something.\n"
	.string "It's quieter down here.$"

Flag7_TrickHousePuzzle6_Text_TunnelADefeat:
	.string "Not bad.\n"
	.string "Maybe you're ready to go deeper.$"

Flag7_TrickHousePuzzle6_Text_TunnelAPostBattle:
	.string "Most people never reach this far beneath\n"
	.string "the campus. Keep pushing if you dare.$"

Flag7_TrickHousePuzzle6_Text_TunnelBIntro:
	.string "Ah, you met my partner already?\p"
	.string "We found these tunnels years ago\n"
	.string "while exploring.\p"
	.string "At first we thought we'd leave again...\p"
	.string "but somehow we never did.$"

Flag7_TrickHousePuzzle6_Text_TunnelBDefeat:
	.string "You're stronger than most explorers.$"

Flag7_TrickHousePuzzle6_Text_TunnelBPostBattle:
	.string "If you keep going... you'll reach parts\n"
	.string "of the tunnels we never mapped.$"
