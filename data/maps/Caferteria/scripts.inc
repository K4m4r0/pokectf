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
	applymovement LOCALID_RYBBEL, Common_Movement_QuestionMark
	waitmovement 0
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	setvar VAR_TEMP_2, 0
	call Caferteria_EventScript_RybbelHandleApproach
	waitmovement 0
	faceplayer
	goto_if_eq VAR_RYBBEL_TERMINAL_HINT, 0, Caferteria_EventScript_RybbelFirstMeeting
	msgbox Caferteria_Text_RybbelReminder, MSGBOX_DEFAULT
	goto Caferteria_EventScript_RybbelConversationEnd

Caferteria_EventScript_RybbelFirstMeeting::
	msgbox Caferteria_Text_RybbelIntro, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelTunnels, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelHistory, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelSystems, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelMission, MSGBOX_DEFAULT
	msgbox Caferteria_Text_RybbelPentester, MSGBOX_DEFAULT
	setvar VAR_RYBBEL_TERMINAL_HINT, 1
	goto Caferteria_EventScript_RybbelConversationEnd

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
	.string "It used to belong to an earlier class.\p"
	.string "Nobody uses it anymore. Nobody even\nremembers it’s there.$"

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
