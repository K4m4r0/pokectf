Flag7_TrickHousePuzzle7_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Flag7_TrickHousePuzzle7_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Flag7_TrickHousePuzzle7_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Flag7_TrickHousePuzzle7_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Flag7_TrickHousePuzzle7_OnFrame
	.byte 0

@ Puzzle Room 7 in RSE uses whatever puzzle Mossdeep Gym uses
@ Because Mossdeep Gym was redesigned for Emerald, theres a good deal of leftover script from the old R/S puzzle

Flag7_TrickHousePuzzle7_OnResume:
	call Flag7_TrickHousePuzzle7_EventScript_UpdateSwitchMetatiles
	end

Flag7_TrickHousePuzzle7_EventScript_UpdateSwitchMetatiles::
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1, Flag7_TrickHousePuzzle7_EventScript_SetSwitch1MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2, Flag7_TrickHousePuzzle7_EventScript_SetSwitch2MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3, Flag7_TrickHousePuzzle7_EventScript_SetSwitch3MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4, Flag7_TrickHousePuzzle7_EventScript_SetSwitch4MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5, Flag7_TrickHousePuzzle7_EventScript_SetSwitch5MetatilesOn
	return

@ Leftover from R/S, none of the below metatile scripts are ever called
Flag7_TrickHousePuzzle7_EventScript_SetSwitch1MetatilesOn::
	setmetatile 13, 17, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Up, FALSE
	setmetatile 12, 16, METATILE_TrickHousePuzzle_Lever_On, TRUE
	return

Flag7_TrickHousePuzzle7_EventScript_SetSwitch2MetatilesOn::
	setmetatile 12, 13, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Up, FALSE
	setmetatile 12, 11, METATILE_TrickHousePuzzle_Lever_On, TRUE
	return

Flag7_TrickHousePuzzle7_EventScript_SetSwitch3MetatilesOn::
	setmetatile 7, 12, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Up, FALSE
	setmetatile 5, 10, METATILE_TrickHousePuzzle_Lever_On, TRUE
	return

Flag7_TrickHousePuzzle7_EventScript_SetSwitch4MetatilesOn::
	setmetatile 6, 6, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Right_Alt, FALSE
	setmetatile 4, 4, METATILE_TrickHousePuzzle_Lever_On, TRUE
	return

Flag7_TrickHousePuzzle7_EventScript_SetSwitch5MetatilesOn::
	setmetatile 8, 4, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Left, FALSE
	setmetatile 7, 5, METATILE_TrickHousePuzzle_Lever_On, TRUE
	return

Flag7_TrickHousePuzzle7_EventScript_SetSwitch1MetatilesOff::
	setmetatile 13, 17, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Down, FALSE
	setmetatile 12, 16, METATILE_TrickHousePuzzle_Lever_Off, TRUE
	return

Flag7_TrickHousePuzzle7_EventScript_SetSwitch2MetatilesOff::
	setmetatile 12, 13, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Left, FALSE
	setmetatile 12, 11, METATILE_TrickHousePuzzle_Lever_Off, TRUE
	return

Flag7_TrickHousePuzzle7_EventScript_SetSwitch3MetatilesOff::
	setmetatile 7, 12, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Down, FALSE
	setmetatile 5, 10, METATILE_TrickHousePuzzle_Lever_Off, TRUE
	return

Flag7_TrickHousePuzzle7_EventScript_SetSwitch4MetatilesOff::
	setmetatile 6, 6, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Left_Alt, FALSE
	setmetatile 4, 4, METATILE_TrickHousePuzzle_Lever_Off, TRUE
	return

Flag7_TrickHousePuzzle7_EventScript_SetSwitch5MetatilesOff::
	setmetatile 8, 4, METATILE_TrickHousePuzzle_Arrow_RedOnBlack_Right, FALSE
	setmetatile 7, 5, METATILE_TrickHousePuzzle_Lever_Off, TRUE
	return

Flag7_TrickHousePuzzle7_OnTransition:
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_7_STATE_2, 1, Flag7_TrickHousePuzzle7_EventScript_TeleportedTransition
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5
	end

Flag7_TrickHousePuzzle7_EventScript_TeleportedTransition::
	end

Flag7_TrickHousePuzzle7_OnLoad:
	call_if_eq VAR_TRICK_HOUSE_PUZZLE_7_STATE_2, 1, Flag7_TrickHousePuzzle7_EventScript_UpdateSwitchMetatiles
	end

Flag7_TrickHousePuzzle7_OnFrame:
	map_script_2 VAR_TRICK_HOUSE_PUZZLE_7_STATE_2, 1, Flag7_TrickHousePuzzle7_EventScript_ClearState2
	.2byte 0

Flag7_TrickHousePuzzle7_EventScript_ClearState2::
	setvar VAR_TRICK_HOUSE_PUZZLE_7_STATE_2, 0
	end

Flag7_TrickHousePuzzle7_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_7_STATE, 0, Flag7_TrickHousePuzzle7_EventScript_FoundScroll
	goto Flag7_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Flag7_TrickHousePuzzle7_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_7_STATE, 1
	goto Flag7_TrickHousePuzzle_EventScript_FoundScroll
	end

@ Unused, leftover from R/S
Flag7_TrickHousePuzzle7_EventScript_TeleportPad::
	lockall
	setvar VAR_TRICK_HOUSE_PUZZLE_7_STATE_2, 1
	warpteleport MAP_FLAG7_TRICK_HOUSE_PUZZLE7, 3, 19
	waitstate
	releaseall
	end

Flag7_TrickHousePuzzle7_EventScript_Archivist::
	trainerbattle_single TRAINER_JOSHUA, Flag7_TrickHousePuzzle7_Text_ArchivistIntro, Flag7_TrickHousePuzzle7_Text_ArchivistDefeat
	msgbox Flag7_TrickHousePuzzle7_Text_ArchivistPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle7_EventScript_SupplyRunner::
	trainerbattle_single TRAINER_PATRICIA, Flag7_TrickHousePuzzle7_Text_SupplyIntro, Flag7_TrickHousePuzzle7_Text_SupplyDefeat
	msgbox Flag7_TrickHousePuzzle7_Text_SupplyPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle7_EventScript_InfrastructureEngineer::
	trainerbattle_single TRAINER_ALEXIS, Flag7_TrickHousePuzzle7_Text_EngineerIntro, Flag7_TrickHousePuzzle7_Text_EngineerDefeat
	msgbox Flag7_TrickHousePuzzle7_Text_EngineerPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle7_EventScript_Veteran::
	trainerbattle_single TRAINER_EVERETT, Flag7_TrickHousePuzzle7_Text_VeteranIntro, Flag7_TrickHousePuzzle7_Text_VeteranDefeat
	msgbox Flag7_TrickHousePuzzle7_Text_VeteranPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle7_EventScript_TunnelBride::
	lockall
	faceplayer
	checktrainerflag TRAINER_ALVARO
	goto_if_eq VAR_RESULT, TRUE, Flag7_TrickHousePuzzle7_EventScript_TunnelCoupleAfter
	trainerbattle_double TRAINER_ALVARO, Flag7_TrickHousePuzzle7_Text_BrideIntro, Flag7_TrickHousePuzzle7_Text_BrideDefeat, Flag7_TrickHousePuzzle7_Text_BrideNotEnough, Flag7_TrickHousePuzzle7_EventScript_TunnelCoupleAfter
	end

Flag7_TrickHousePuzzle7_EventScript_TunnelGroom::
	lockall
	faceplayer
	checktrainerflag TRAINER_ALVARO
	goto_if_eq VAR_RESULT, TRUE, Flag7_TrickHousePuzzle7_EventScript_TunnelCoupleAfter
	trainerbattle_double TRAINER_ALVARO, Flag7_TrickHousePuzzle7_Text_GroomIntro, Flag7_TrickHousePuzzle7_Text_GroomDefeat, Flag7_TrickHousePuzzle7_Text_BrideNotEnough, Flag7_TrickHousePuzzle7_EventScript_TunnelCoupleAfter
	end

Flag7_TrickHousePuzzle7_EventScript_TunnelCoupleAfter::
	msgbox Flag7_TrickHousePuzzle7_Text_TunnelCouplePostBattle, MSGBOX_DEFAULT
	releaseall
	end

@ All the below switch scripts are unused leftover from R/S
Flag7_TrickHousePuzzle7_EventScript_Switch1::
	lockall
	delay 32
	call_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1, Flag7_TrickHousePuzzle7_EventScript_SetSwitch1MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1, Flag7_TrickHousePuzzle7_EventScript_SetSwitch1MetatilesOff
	special DrawWholeMapView
	playse SE_CLICK
	goto_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1, Flag7_TrickHousePuzzle7_EventScript_SetSwitch1On
	goto_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1, Flag7_TrickHousePuzzle7_EventScript_SetSwitch1Off
	end

Flag7_TrickHousePuzzle7_EventScript_Switch2::
	lockall
	delay 32
	call_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2, Flag7_TrickHousePuzzle7_EventScript_SetSwitch2MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2, Flag7_TrickHousePuzzle7_EventScript_SetSwitch2MetatilesOff
	special DrawWholeMapView
	playse SE_CLICK
	goto_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2, Flag7_TrickHousePuzzle7_EventScript_SetSwitch2On
	goto_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2, Flag7_TrickHousePuzzle7_EventScript_SetSwitch2Off
	end

Flag7_TrickHousePuzzle7_EventScript_Switch3::
	lockall
	delay 32
	call_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3, Flag7_TrickHousePuzzle7_EventScript_SetSwitch3MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3, Flag7_TrickHousePuzzle7_EventScript_SetSwitch3MetatilesOff
	special DrawWholeMapView
	playse SE_CLICK
	goto_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3, Flag7_TrickHousePuzzle7_EventScript_SetSwitch3On
	goto_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3, Flag7_TrickHousePuzzle7_EventScript_SetSwitch3Off
	end

Flag7_TrickHousePuzzle7_EventScript_Switch4::
	lockall
	delay 32
	call_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4, Flag7_TrickHousePuzzle7_EventScript_SetSwitch4MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4, Flag7_TrickHousePuzzle7_EventScript_SetSwitch4MetatilesOff
	special DrawWholeMapView
	playse SE_CLICK
	goto_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4, Flag7_TrickHousePuzzle7_EventScript_SetSwitch4On
	goto_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4, Flag7_TrickHousePuzzle7_EventScript_SetSwitch4Off
	end

Flag7_TrickHousePuzzle7_EventScript_Switch5::
	lockall
	delay 32
	call_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5, Flag7_TrickHousePuzzle7_EventScript_SetSwitch5MetatilesOn
	call_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5, Flag7_TrickHousePuzzle7_EventScript_SetSwitch5MetatilesOff
	special DrawWholeMapView
	playse SE_CLICK
	goto_if_unset FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5, Flag7_TrickHousePuzzle7_EventScript_SetSwitch5On
	goto_if_set FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5, Flag7_TrickHousePuzzle7_EventScript_SetSwitch5Off
	end

@ All the below switch scripts are unused leftover from R/S
Flag7_TrickHousePuzzle7_EventScript_SetSwitch1On::
	setflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1
	releaseall
	end

Flag7_TrickHousePuzzle7_EventScript_SetSwitch1Off::
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1
	releaseall
	end

Flag7_TrickHousePuzzle7_EventScript_SetSwitch2On::
	setflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2
	releaseall
	end

Flag7_TrickHousePuzzle7_EventScript_SetSwitch2Off::
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2
	releaseall
	end

Flag7_TrickHousePuzzle7_EventScript_SetSwitch3On::
	setflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3
	releaseall
	end

Flag7_TrickHousePuzzle7_EventScript_SetSwitch3Off::
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3
	releaseall
	end

Flag7_TrickHousePuzzle7_EventScript_SetSwitch4On::
	setflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4
	releaseall
	end

Flag7_TrickHousePuzzle7_EventScript_SetSwitch4Off::
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4
	releaseall
	end

Flag7_TrickHousePuzzle7_EventScript_SetSwitch5On::
	setflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5
	releaseall
	end

Flag7_TrickHousePuzzle7_EventScript_SetSwitch5Off::
	clearflag FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5
	releaseall
	end

@ From here is where the new, actually used puzzle scripts begin
Flag7_TrickHousePuzzle7_EventScript_YellowButton::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle TRUE
	moverotatingtileobjects 0
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

Flag7_TrickHousePuzzle7_EventScript_BlueButton::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle TRUE
	moverotatingtileobjects 1
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

Flag7_TrickHousePuzzle7_EventScript_GreenButton::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle TRUE
	moverotatingtileobjects 2
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

Flag7_TrickHousePuzzle7_EventScript_PurpleButton::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle TRUE
	moverotatingtileobjects 3
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

@ Unused
Flag7_TrickHousePuzzle7_EventScript_RedButton::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle TRUE
	moverotatingtileobjects 4
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

Flag7_TrickHousePuzzle7_EventScript_Joshua::
	trainerbattle_single TRAINER_JOSHUA, Flag7_TrickHousePuzzle7_Text_JoshuaIntro, Flag7_TrickHousePuzzle7_Text_JoshuaDefeat
	msgbox Flag7_TrickHousePuzzle7_Text_JoshuaPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle7_EventScript_Patricia::
	trainerbattle_single TRAINER_PATRICIA, Flag7_TrickHousePuzzle7_Text_PatriciaIntro, Flag7_TrickHousePuzzle7_Text_PatriciaDefeat
	msgbox Flag7_TrickHousePuzzle7_Text_PatriciaPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle7_EventScript_Alexis::
	trainerbattle_single TRAINER_ALEXIS, Flag7_TrickHousePuzzle7_Text_AlexisIntro, Flag7_TrickHousePuzzle7_Text_AlexisDefeat
	msgbox Flag7_TrickHousePuzzle7_Text_AlexisPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle7_EventScript_Mariela::
	trainerbattle_single TRAINER_MARIELA, Flag7_TrickHousePuzzle7_Text_MarielaIntro, Flag7_TrickHousePuzzle7_Text_MarielaDefeat
	msgbox Flag7_TrickHousePuzzle7_Text_MarielaPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle7_EventScript_Alvaro::
	trainerbattle_single TRAINER_ALVARO, Flag7_TrickHousePuzzle7_Text_AlvaroIntro, Flag7_TrickHousePuzzle7_Text_AlvaroDefeat
	msgbox Flag7_TrickHousePuzzle7_Text_AlvaroPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle7_EventScript_Everett::
	trainerbattle_single TRAINER_EVERETT, Flag7_TrickHousePuzzle7_Text_EverettIntro, Flag7_TrickHousePuzzle7_Text_EverettDefeat
	msgbox Flag7_TrickHousePuzzle7_Text_EverettPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle7_Text_ArchivistIntro:
	.string "Oh! A new visitor.\p"
	.string "Most people think these tunnels\n"
	.string "are just maintenance corridors.\p"
	.string "But there is history down here.\p"
	.string "Old systems... forgotten rooms...\n"
	.string "entire stories beneath the campus.$"

Flag7_TrickHousePuzzle7_Text_ArchivistDefeat:
	.string "Fascinating.$"

Flag7_TrickHousePuzzle7_Text_ArchivistPostBattle:
	.string "Maybe you belong in our little\n"
	.string "community.$"

Flag7_TrickHousePuzzle7_Text_SupplyIntro:
	.string "You wouldn't believe how much food\n"
	.string "disappears down here.\p"
	.string "The cafeteria thinks it's\n"
	.string "accounting errors.\p"
	.string "We call it logistics.$"

Flag7_TrickHousePuzzle7_Text_SupplyDefeat:
	.string "Hey... if you're staying down here,\n"
	.string "you're welcome to join dinner.$"

Flag7_TrickHousePuzzle7_Text_SupplyPostBattle:
	.string "We keep the meals moving.\n"
	.string "Stick with us and eat well.$"

Flag7_TrickHousePuzzle7_Text_EngineerIntro:
	.string "You probably think these tunnels\n"
	.string "are abandoned. They aren't.\p"
	.string "Someone has to keep the underground\n"
	.string "running.$"

Flag7_TrickHousePuzzle7_Text_EngineerDefeat:
	.string "Good battle.\n"
	.string "Maybe you really can handle\n"
	.string "what lies deeper.$"

Flag7_TrickHousePuzzle7_Text_EngineerPostBattle:
	.string "If the power flickers, it's because\n"
	.string "we're rerouting the whole grid.$"

Flag7_TrickHousePuzzle7_Text_VeteranIntro:
	.string "I've lived in these tunnels longer\n"
	.string "than most students stay at the university.\p"
	.string "People come and go.\p"
	.string "But down here... the community stays.$"

Flag7_TrickHousePuzzle7_Text_VeteranDefeat:
	.string "You fight like someone who understands\n"
	.string "the tunnels.$"

Flag7_TrickHousePuzzle7_Text_VeteranPostBattle:
	.string "People come and go up top.\n"
	.string "Down here, the stories linger.$"

Flag7_TrickHousePuzzle7_Text_BrideIntro:
	.string "Oh! Visitors!\p"
	.string "You're just in time. We recently had\n"
	.string "a small celebration down here...\p"
	.string "a wedding.$"

Flag7_TrickHousePuzzle7_Text_BrideDefeat:
	.string "That was wonderful!$"

Flag7_TrickHousePuzzle7_Text_GroomIntro:
	.string "Turns out you don't need a fancy venue\n"
	.string "to get married.\p"
	.string "Just good company and strong POKéMON.\p"
	.string "Let's show them.$"

Flag7_TrickHousePuzzle7_Text_GroomDefeat:
	.string "Battles like that remind us why\n"
	.string "we stayed down here.$"

Flag7_TrickHousePuzzle7_Text_BrideNotEnough:
	.string "We need two strong TRAINERS\n"
	.string "for this battle.$"

Flag7_TrickHousePuzzle7_Text_TunnelCouplePostBattle:
	.string "That was wonderful!\n"
	.string "Battles like that remind us why\n"
	.string "we stayed down here.$"

Flag7_TrickHousePuzzle7_Text_TunnelAIntro:
	.string "Oh... another visitor.\p"
	.string "We used to work on the upper campus.\p"
	.string "But after a while... we realized something.\n"
	.string "It's quieter down here.$"

Flag7_TrickHousePuzzle7_Text_TunnelADefeat:
	.string "Not bad.\n"
	.string "Maybe you're ready to go deeper.$"

Flag7_TrickHousePuzzle7_Text_TunnelAPostBattle:
	.string "Most people never reach this far beneath\n"
	.string "the campus. Keep pushing if you dare.$"

Flag7_TrickHousePuzzle7_Text_TunnelBIntro:
	.string "Ah, you met my partner already?\p"
	.string "We found these tunnels years ago\n"
	.string "while exploring.\p"
	.string "At first we thought we'd leave again...\p"
	.string "but somehow we never did.$"

Flag7_TrickHousePuzzle7_Text_TunnelBDefeat:
	.string "You're stronger than most explorers.$"

Flag7_TrickHousePuzzle7_Text_TunnelBPostBattle:
	.string "If you keep going... you'll reach parts\n"
	.string "of the tunnels we never mapped.$"
Flag7_TrickHousePuzzle7_Text_WroteSecretCodeLockOpened::
	.string "{PLAYER} wrote down the secret code\n"
	.string "on the door.\p"
	.string "“TRICK MASTER is huggable.”\n"
	.string "… … … … … … … …\p"
	.string "The lock clicked open!$"

Flag7_TrickHousePuzzle7_Text_JoshuaIntro:
	.string "The TRICK MASTER always vanishes\n"
	.string "like smoke. How does he do it?$"

Flag7_TrickHousePuzzle7_Text_JoshuaDefeat:
	.string "Aiyeeeh! You're much too strong!\n"
	.string "How do you do it?$"

Flag7_TrickHousePuzzle7_Text_JoshuaPostBattle:
	.string "I wish I could appear and disappear as\n"
	.string "if I were smoke, too.$"

Flag7_TrickHousePuzzle7_Text_PatriciaIntro:
	.string "Going around the same spot…\n"
	.string "It begets ill fortune…$"

Flag7_TrickHousePuzzle7_Text_PatriciaDefeat:
	.string "Defeated!\n"
	.string "It's a bad sign…$"

Flag7_TrickHousePuzzle7_Text_PatriciaPostBattle:
	.string "I've circled the same spot over ten\n"
	.string "times now… It's ill fortune…$"

Flag7_TrickHousePuzzle7_Text_AlexisIntro:
	.string "Whoever wins will get through here\n"
	.string "first. That's the feeling I get.$"

Flag7_TrickHousePuzzle7_Text_AlexisDefeat:
	.string "Oh!\n"
	.string "Well, go ahead, then!$"

Flag7_TrickHousePuzzle7_Text_AlexisPostBattle:
	.string "You're solving all the puzzles in the\n"
	.string "TRICK HOUSE. That's the feeling I get.$"

Flag7_TrickHousePuzzle7_Text_MarielaIntro:
	.string "Nufufufu, here at last!\n"
	.string "Let's get right with it!$"

Flag7_TrickHousePuzzle7_Text_MarielaDefeat:
	.string "You're so casual about winning!$"

Flag7_TrickHousePuzzle7_Text_MarielaPostBattle:
	.string "Humph! I'm not upset!\n"
	.string "Not me!$"

Flag7_TrickHousePuzzle7_Text_AlvaroIntro:
	.string "I ever so closely watched you coming!$"

Flag7_TrickHousePuzzle7_Text_AlvaroDefeat:
	.string "This outcome I didn't see coming…$"

Flag7_TrickHousePuzzle7_Text_AlvaroPostBattle:
	.string "Well, anyway, we both picked a weird\n"
	.string "place to get acquainted.\p"
	.string "As one weirdo to another,\n"
	.string "let's do our best!$"

Flag7_TrickHousePuzzle7_Text_EverettIntro:
	.string "It's awfully cramped in here…$"

Flag7_TrickHousePuzzle7_Text_EverettDefeat:
	.string "Oh, yes, strong you are.$"

Flag7_TrickHousePuzzle7_Text_EverettPostBattle:
	.string "I was hoping to switch places with you\n"
	.string "when I beat you, but…$"
