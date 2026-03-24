Caferteria_MapScripts::
	.byte 0

Caferteria_EventScript_Rybbel::
	lock
	call Caferteria_EventScript_RybbelConversation
	release
	end

Caferteria_EventScript_RybbelSightTrigger::
	lockall
	call Caferteria_EventScript_RybbelConversation
	releaseall
	end

Caferteria_EventScript_RybbelConversation::
	goto_if_set FLAG_HIDE_RYBBEL, Caferteria_EventScript_RybbelAlreadyGone
	goto_if_eq VAR_RYBBEL_TERMINAL_HINT, 0, Caferteria_EventScript_RybbelFirstMeeting
	checkitem ITEM_CTF_TERMINAL
	goto_if_eq VAR_RESULT, TRUE, Caferteria_EventScript_RybbelHasTerminal
	goto Caferteria_EventScript_RybbelNeedsTerminal

Caferteria_EventScript_RybbelAlreadyGone::
	return

Caferteria_EventScript_RybbelFirstMeeting::
	call Caferteria_EventScript_RybbelConversationSetup
	msgbox Caferteria_Text_RybbelIntro, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelTunnels, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelHistory, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelSystems, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelMission, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelPentester, MSGBOX_DEFAULT
	setvar VAR_RYBBEL_TERMINAL_HINT, 1
	goto Caferteria_EventScript_RybbelConversationEnd

Caferteria_EventScript_RybbelHasTerminal::
	call Caferteria_EventScript_RybbelConversationSetup
	msgbox Caferteria_Text_RybbelTerminalFound1, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelTerminalFound2, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelTerminalFound3, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelTerminalFound4, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelTerminalFound5, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelTerminalFound6, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelTerminalFound7, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelTerminalFound8, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelTerminalFound9, MSGBOX_DEFAULT
	goto Caferteria_EventScript_RybbelLeave

Caferteria_EventScript_RybbelNeedsTerminal::
	setvar VAR_TEMP_2, 0
	faceplayer
	msgbox Caferteria_Text_RybbelReminder, MSGBOX_DEFAULT
	goto Caferteria_EventScript_RybbelConversationEnd

Caferteria_EventScript_RybbelConversationSetup::
	applymovement LOCALID_RYBBEL, Common_Movement_QuestionMark
	waitmovement 0
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	setvar VAR_TEMP_2, 0
	call Caferteria_EventScript_RybbelHandleApproach
	waitmovement 0
	faceplayer
	return

Caferteria_EventScript_RybbelLeave::
	compare VAR_TEMP_2, 0
	goto_if_ne Caferteria_EventScript_RybbelLeaveStraight
	compare VAR_TEMP_0, 25
	goto_if_ne Caferteria_EventScript_RybbelLeaveStraight
	compare VAR_TEMP_1, 16
	goto_if_ne Caferteria_EventScript_RybbelLeaveStraight
	applymovement LOCALID_RYBBEL, Caferteria_Movement_RybbelLeaveFront
	goto Caferteria_EventScript_RybbelLeaveDespawn

Caferteria_EventScript_RybbelLeaveStraight::
	applymovement LOCALID_RYBBEL, Caferteria_Movement_RybbelLeaveStraight
	goto Caferteria_EventScript_RybbelLeaveDespawn

Caferteria_EventScript_RybbelLeaveDespawn::
	waitmovement 0
	setflag FLAG_RYBBEL_FOREST_READY
	clearflag FLAG_HIDE_PETALBURG_WOODS_RYBBEL
	setflag FLAG_HIDE_RYBBEL
	removeobject LOCALID_RYBBEL
	return

Caferteria_EventScript_RybbelConversationEnd::
	call Caferteria_EventScript_RybbelHandleReturn
	waitmovement 0
	return

Caferteria_EventScript_RybbelHandleApproach::
	compare VAR_TEMP_1, 16
	goto_if_lt Caferteria_EventScript_RybbelApproachFromSide
	goto Caferteria_EventScript_RybbelApproachFromSouth

Caferteria_EventScript_RybbelApproachFromSide::
	compare VAR_TEMP_0, 25
	goto_if_gt Caferteria_EventScript_RybbelApproachFromEast
	compare VAR_TEMP_0, 25
	goto_if_lt Caferteria_EventScript_RybbelApproachFromWest
	return

Caferteria_EventScript_RybbelApproachFromEast::
	turnobject LOCALID_PLAYER, DIR_WEST
	return

Caferteria_EventScript_RybbelApproachFromWest::
	turnobject LOCALID_PLAYER, DIR_EAST
	return

Caferteria_EventScript_RybbelApproachFromSouth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	copyvar VAR_TEMP_2, VAR_TEMP_1
	subvar VAR_TEMP_2, 16
	compare VAR_TEMP_2, 0
	goto_if_le Caferteria_EventScript_RybbelApproachNoMove
	compare VAR_TEMP_2, 1
	goto_if_eq Caferteria_EventScript_RybbelApproachOneStep
	compare VAR_TEMP_2, 2
	goto_if_eq Caferteria_EventScript_RybbelApproachTwoSteps
	compare VAR_TEMP_2, 3
	goto_if_eq Caferteria_EventScript_RybbelApproachThreeSteps
	goto Caferteria_EventScript_RybbelApproachThreeSteps

Caferteria_EventScript_RybbelApproachNoMove::
	setvar VAR_TEMP_2, 0
	return

Caferteria_EventScript_RybbelApproachOneStep::
	applymovement LOCALID_RYBBEL, Caferteria_Movement_RybbelStepDown
	setvar VAR_TEMP_2, 1
	return

Caferteria_EventScript_RybbelApproachTwoSteps::
	applymovement LOCALID_RYBBEL, Caferteria_Movement_RybbelStepDownTwice
	setvar VAR_TEMP_2, 2
	return

Caferteria_EventScript_RybbelApproachThreeSteps::
	applymovement LOCALID_RYBBEL, Caferteria_Movement_RybbelStepDownThrice
	setvar VAR_TEMP_2, 3
	return

Caferteria_EventScript_RybbelHandleReturn::
	compare VAR_TEMP_2, 0
	goto_if_eq Caferteria_EventScript_RybbelReturnNoMove
	compare VAR_TEMP_2, 1
	goto_if_eq Caferteria_EventScript_RybbelReturnOneStep
	compare VAR_TEMP_2, 2
	goto_if_eq Caferteria_EventScript_RybbelReturnTwoSteps
	goto Caferteria_EventScript_RybbelReturnThreeSteps

Caferteria_EventScript_RybbelReturnNoMove::
	return

Caferteria_EventScript_RybbelReturnOneStep::
	applymovement LOCALID_RYBBEL, Caferteria_Movement_RybbelStepUp
	return

Caferteria_EventScript_RybbelReturnTwoSteps::
	applymovement LOCALID_RYBBEL, Caferteria_Movement_RybbelStepUpTwice
	return

Caferteria_EventScript_RybbelReturnThreeSteps::
	applymovement LOCALID_RYBBEL, Caferteria_Movement_RybbelStepUpThrice
	return

Caferteria_Text_RybbelIntro:
	.string "Rybbel: Good you came!\p"
	.string "BENEATH this cafeteria…\nthere’s an old service level.$"

Caferteria_Text_RybbelTunnels:
	.string "Maintenance tunnels. Pipes. Power lines.\p"
	.string "And somewhere down there…\nthere’s an old CTF terminal.$"

Caferteria_Text_RybbelHistory:
	.string "This originally belonged to an\n"
	.string "older class\p"
	.string "Nobody uses it anymore. Nobody\n"
	.string "even remembers it is there.$"

Caferteria_Text_RybbelSystems:
	.string "But systems don’t disappear.\p"
	.string "They just move BENEATH the surface.$"

Caferteria_Text_RybbelMission:
	.string "Go down there. Find the terminal.\p"
	.string "And bring me whatever you discover.$"

Caferteria_Text_RybbelPentester:
	.string "As a physical pentester…\p"
	.string "I’m sure you’ll manage.$"

Caferteria_Text_RybbelReminder:
	.string "Rybbel: You should get the terminal.$"

Caferteria_Text_RybbelTerminalFound1:
	.string "Prof. Rybbel: So you actually found it.\p"
	.string "The old CTF terminal\nbeneath the cafeteria.\p"
	.string "Not bad.$"

Caferteria_Text_RybbelTerminalFound2:
	.string " Prof. Rybbel: Most people spend\n their entire day on the surface.\p"
	.string "Eating, studying, walking around.\p"
	.string "Never wondering what runs\nbeneath their feet.$"

Caferteria_Text_RybbelTerminalFound3:
	.string "Prof. Rybbel: Pipes. Power lines.\nNetwork cables.\p"
	.string "Entire systems\nhidden beneath the surface.$"

Caferteria_Text_RybbelTerminalFound4:
	.string "Prof. Rybbel: As a physical pentester\nyou already proved something important.\p"
	.string "You know how to reach places\nothers never even look at.$"

Caferteria_Text_RybbelTerminalFound5:
	.string "Prof. Rybbel: Good.\p"
	.string "Because the real challenge\nisn't here.$"

Caferteria_Text_RybbelTerminalFound6:
	.string "Prof. Rybbel: Take the terminal.\p"
	.string "And meet me in the forest\nabove Rheinpromenade.$"

Caferteria_Text_RybbelTerminalFound7:
	.string "Prof. Rybbel: There's a clearing there.\p"
	.string "Quiet. Isolated.\p"
	.string "Perfect for what comes next.$"

Caferteria_Text_RybbelTerminalFound8:
	.string "Prof. Rybbel: Bring the terminal with you.\p"
	.string "I'll be waiting.$"

Caferteria_Text_RybbelTerminalFound9:
	.string "Prof. Rybbel: And {PLAYER}…\p"
	.string "when you get there,\p"
	.string "try to look beneath the surface.$"

Caferteria_Movement_RybbelStepDown:
	walk_down
	step_end

Caferteria_Movement_RybbelStepDownTwice:
	walk_down
	walk_down
	step_end

Caferteria_Movement_RybbelStepDownThrice:
	walk_down
	walk_down
	walk_down
	step_end

Caferteria_Movement_RybbelStepUp:
	walk_up
	step_end

Caferteria_Movement_RybbelStepUpTwice:
	walk_up
	walk_up
	step_end

Caferteria_Movement_RybbelStepUpThrice:
	walk_up
	walk_up
	walk_up
	step_end

Caferteria_Movement_RybbelLeaveStraight:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Caferteria_Movement_RybbelLeaveFront:
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end
