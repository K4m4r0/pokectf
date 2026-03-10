#define CTF_FLAG_ID_FLAG7 7

RybbelPreForest_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RybbelPreForest_OnLoad
	.byte 0

RybbelPreForest_OnLoad::
	setflag FLAG_HIDE_RYBBEL_PRE_FOREST_GIRATINA
	goto_if_set FLAG_RYBBEL_PRE_FOREST_TERMINAL_PLACED, RybbelPreForest_OnLoadTerminalPlaced
	setflag FLAG_HIDE_RYBBEL_PRE_FOREST_TERMINAL
	goto RybbelPreForest_OnLoadEnd
RybbelPreForest_OnLoadTerminalPlaced::
	clearflag FLAG_HIDE_RYBBEL_PRE_FOREST_TERMINAL
RybbelPreForest_OnLoadEnd::
	end

RybbelPreForest_EventScript_Approach::
	goto_if_set FLAG_RYBBEL_PRE_FOREST_TERMINAL_PLACED, RybbelPreForest_EventScript_ApproachEnd
	lockall
	call RybbelPreForest_EventScript_MovePlayerToApproach
	applymovement LOCALID_RYBBEL_PRE_FOREST_RYBBEL, RybbelPreForest_Movement_RybbelFaceLeft
	waitmovement 0
	call RybbelPreForest_EventScript_RunScene
	releaseall
	end
RybbelPreForest_EventScript_ApproachEnd::
	end

RybbelPreForest_EventScript_Rybbel::
	lock
	faceplayer
	goto_if_set FLAG_RYBBEL_PRE_FOREST_TERMINAL_PLACED, RybbelPreForest_EventScript_RybbelRepeat
	call RybbelPreForest_EventScript_MovePlayerToApproach
	applymovement LOCALID_RYBBEL_PRE_FOREST_RYBBEL, RybbelPreForest_Movement_RybbelFaceLeft
	waitmovement 0
	call RybbelPreForest_EventScript_RunScene
	release
	end

RybbelPreForest_EventScript_RybbelRepeat::
	msgbox RybbelPreForest_Text_RybbelLookBeneath, MSGBOX_DEFAULT
	release
	end

RybbelPreForest_EventScript_Terminal::
	lock
	faceplayer
	goto_if_set FLAG_CTF_FLAG7_TERMINAL_DONE, RybbelPreForest_EventScript_TerminalAlreadySolved
	msgbox RybbelPreForest_Text_TerminalPrompt, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8000, CTF_FLAG_ID_FLAG7
	callnative Ctf_FlagTerminal
	waitstate
	compare VAR_RESULT, TRUE
	goto_if_eq RybbelPreForest_EventScript_TerminalSuccess
	msgbox RybbelPreForest_Text_TerminalWrong, MSGBOX_DEFAULT
	release
	end

RybbelPreForest_EventScript_TerminalSuccess:
	setflag FLAG_CTF_FLAG7_TERMINAL_DONE
	msgbox RybbelPreForest_Text_TerminalSuccess, MSGBOX_DEFAULT
	release
	end

RybbelPreForest_EventScript_TerminalAlreadySolved:
	msgbox RybbelPreForest_Text_TerminalSuccess, MSGBOX_DEFAULT
	release
	end

RybbelPreForest_EventScript_BeneathSign::
	msgbox RybbelPreForest_Text_BeneathSign, MSGBOX_SIGN
	end

RybbelPreForest_EventScript_RunScene::
	msgbox RybbelPreForest_Text_RybbelPlace, MSGBOX_DEFAULT
	msgbox RybbelPreForest_Text_RybbelQuiet, MSGBOX_DEFAULT
	msgbox RybbelPreForest_Text_RybbelPattern, MSGBOX_DEFAULT
	msgbox RybbelPreForest_Text_RybbelClearing, MSGBOX_DEFAULT
	msgbox RybbelPreForest_Text_RybbelCenter, MSGBOX_DEFAULT
	call RybbelPreForest_EventScript_MovePlayerToCenter
	setflag FLAG_RYBBEL_PRE_FOREST_TERMINAL_PLACED
	clearflag FLAG_HIDE_RYBBEL_PRE_FOREST_TERMINAL
	addobject LOCALID_RYBBEL_PRE_FOREST_TERMINAL
	msgbox RybbelPreForest_Text_RybbelGood, MSGBOX_DEFAULT
	msgbox RybbelPreForest_Text_RybbelAnalysisA, MSGBOX_DEFAULT
	msgbox RybbelPreForest_Text_RybbelAnalysisB, MSGBOX_DEFAULT
	msgbox RybbelPreForest_Text_RybbelAnalysisC, MSGBOX_DEFAULT
	msgbox RybbelPreForest_Text_RybbelTurnOn, MSGBOX_DEFAULT
	return

RybbelPreForest_EventScript_MovePlayerToApproach::
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
RybbelPreForest_MoveApproachHorizontalLoop::
	compare VAR_TEMP_0, 23
	goto_if_eq RybbelPreForest_MoveApproachVertical
	goto_if_lt RybbelPreForest_MoveApproachNeedRight
RybbelPreForest_MoveApproachNeedLeft:
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerStepLeft
	waitmovement 0
	subvar VAR_TEMP_0, 1
	goto RybbelPreForest_MoveApproachHorizontalLoop
RybbelPreForest_MoveApproachNeedRight:
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerStepRight
	waitmovement 0
	addvar VAR_TEMP_0, 1
	goto RybbelPreForest_MoveApproachHorizontalLoop

RybbelPreForest_MoveApproachVertical:
	compare VAR_TEMP_1, 7
	goto_if_eq RybbelPreForest_MoveApproachDone
	goto_if_lt RybbelPreForest_MoveApproachNeedDown
RybbelPreForest_MoveApproachNeedUp:
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerStepUp
	waitmovement 0
	subvar VAR_TEMP_1, 1
	goto RybbelPreForest_MoveApproachVertical
RybbelPreForest_MoveApproachNeedDown:
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerStepDown
	waitmovement 0
	addvar VAR_TEMP_1, 1
	goto RybbelPreForest_MoveApproachVertical

RybbelPreForest_MoveApproachDone:
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerFaceRight
	waitmovement 0
	return

RybbelPreForest_EventScript_MovePlayerToCenter::
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
RybbelPreForest_MovePlayerHorizontalLoop::
	compare VAR_TEMP_0, 23
	goto_if_eq RybbelPreForest_MovePlayerVertical
	goto_if_lt RybbelPreForest_MovePlayerHorizontalNeedRight
RybbelPreForest_MovePlayerHorizontalNeedLeft:
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerStepLeft
	waitmovement 0
	subvar VAR_TEMP_0, 1
	goto RybbelPreForest_MovePlayerHorizontalLoop
RybbelPreForest_MovePlayerHorizontalNeedRight:
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerStepRight
	waitmovement 0
	addvar VAR_TEMP_0, 1
	goto RybbelPreForest_MovePlayerHorizontalLoop

RybbelPreForest_MovePlayerVertical:
	compare VAR_TEMP_1, 5
	goto_if_eq RybbelPreForest_MovePlayerDone
	goto_if_lt RybbelPreForest_MovePlayerVerticalNeedDown
RybbelPreForest_MovePlayerVerticalNeedUp:
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerStepUp
	waitmovement 0
	subvar VAR_TEMP_1, 1
	goto RybbelPreForest_MovePlayerVertical
RybbelPreForest_MovePlayerVerticalNeedDown:
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerStepDown
	waitmovement 0
	addvar VAR_TEMP_1, 1
	goto RybbelPreForest_MovePlayerVertical

RybbelPreForest_MovePlayerDone:
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerFaceUp
	waitmovement 0
	return

RybbelPreForest_Movement_PlayerStepLeft:
	walk_left
	step_end

RybbelPreForest_Movement_PlayerStepRight:
	walk_right
	step_end

RybbelPreForest_Movement_PlayerStepUp:
	walk_up
	step_end

RybbelPreForest_Movement_PlayerStepDown:
	walk_down
	step_end

RybbelPreForest_Movement_PlayerFaceUp:
	face_up
	step_end

RybbelPreForest_Movement_PlayerFaceRight:
	face_right
	step_end

RybbelPreForest_Movement_RybbelFaceLeft:
	face_left
	step_end

RybbelPreForest_Text_RybbelPlace:
	.string "Prof. Rybbel: This is the place.$"

RybbelPreForest_Text_RybbelQuiet:
	.string "Quiet.\nFar away from the campus.$"

RybbelPreForest_Text_RybbelPattern:
	.string "Do you see the pattern\nin the grass?$"

RybbelPreForest_Text_RybbelClearing:
	.string "This clearing has been here\nlong before the university.$"

RybbelPreForest_Text_RybbelCenter:
	.string "Put the terminal\nright in the center.\p"
	.string "Exactly there.$"

RybbelPreForest_Text_RybbelGood:
	.string "Good.\p"
	.string "Now listen carefully.$"

RybbelPreForest_Text_RybbelAnalysisA:
	.string "Most people look at systems\nfrom the outside.\p"
	.string "They read what is visible.\p"
	.string "They trust the surface.$"

RybbelPreForest_Text_RybbelAnalysisB:
	.string "But real analysis starts\nsomewhere else.\p"
	.string "Beneath the interface.\p"
	.string "Beneath the code.\p"
	.string "Beneath everything.$"

RybbelPreForest_Text_RybbelAnalysisC:
	.string "Only then you start to see\nhow things truly work.$"

RybbelPreForest_Text_RybbelTurnOn:
	.string "Turn on the terminal.\p"
	.string "Let's see\nwhat lies beneath.$"

RybbelPreForest_Text_RybbelLookBeneath:
	.string "Prof. Rybbel: Look beneath.$"

RybbelPreForest_Text_TerminalPrompt:
	.string "The terminal awaits\nyour command.$"

RybbelPreForest_Text_TerminalWrong:
	.string "ACCESS DENIED.$"

RybbelPreForest_Text_TerminalSuccess:
	.string "SUCCESS!$"

RybbelPreForest_Text_BeneathSign:
	.string "BENEATH: UkVWM1JTRUlU$"
