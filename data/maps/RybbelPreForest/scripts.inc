#define CTF_FLAG_ID_FLAG7 7

RybbelPreForest_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RybbelPreForest_OnLoad
	.byte 0

RybbelPreForest_OnLoad::
 	goto_if_set FLAG_DEFEATED_GIRATINA, RybbelPreForest_OnLoadGiratinaDefeated
	goto_if_set FLAG_RYBBEL_GIRATINA_REVEALED, RybbelPreForest_OnLoadGiratinaShown
	setflag FLAG_HIDE_RYBBEL_PRE_FOREST_GIRATINA
	goto RybbelPreForest_OnLoadCheckTerminal
RybbelPreForest_OnLoadGiratinaDefeated::
	setflag FLAG_HIDE_RYBBEL_PRE_FOREST_GIRATINA
	goto RybbelPreForest_OnLoadCheckTerminal
RybbelPreForest_OnLoadGiratinaShown::
	clearflag FLAG_HIDE_RYBBEL_PRE_FOREST_GIRATINA
RybbelPreForest_OnLoadCheckTerminal::
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
	goto_if_set FLAG_RYBBEL_GIRATINA_REVEALED, RybbelPreForest_EventScript_RybbelRepeatPost
	msgbox RybbelPreForest_Text_RybbelLookBeneath, MSGBOX_DEFAULT
	release
	end
RybbelPreForest_EventScript_RybbelRepeatPost::
	msgbox RybbelPreForest_Text_RybbelPostPrompt, MSGBOX_DEFAULT
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
	applymovement LOCALID_RYBBEL_PRE_FOREST_RYBBEL, RybbelPreForest_Movement_RybbelFaceUp
	compare VAR_RESULT, TRUE
	goto_if_eq RybbelPreForest_EventScript_TerminalSuccess
	msgbox RybbelPreForest_Text_TerminalWrong, MSGBOX_DEFAULT
	release
	end

RybbelPreForest_EventScript_TerminalSuccess:
	setflag FLAG_CTF_FLAG7_TERMINAL_DONE
	msgbox RybbelPreForest_Text_TerminalSuccess, MSGBOX_DEFAULT
	closemessage
	call RybbelPreForest_EventScript_Awakening
	release
	end

RybbelPreForest_EventScript_TerminalAlreadySolved:
	msgbox RybbelPreForest_Text_TerminalAlready, MSGBOX_DEFAULT
	release
	end


RybbelPreForest_EventScript_Giratina::
	goto_if_set FLAG_DEFEATED_GIRATINA, RybbelPreForest_EventScript_GiratinaGone
	goto_if_set FLAG_RYBBEL_GIRATINA_REVEALED, RybbelPreForest_EventScript_GiratinaBegin
	msgbox RybbelPreForest_Text_RybbelLookBeneath, MSGBOX_DEFAULT
	return

RybbelPreForest_EventScript_GiratinaBegin::
	lockall
	setwildbattle SPECIES_GIRATINA_ORIGIN, 70, ITEM_NONE
	special BattleSetup_StartScriptedWildBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, RybbelPreForest_EventScript_GiratinaDefeated
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, RybbelPreForest_EventScript_GiratinaDefeated
	releaseall
	return

RybbelPreForest_EventScript_GiratinaDefeated::
	setflag FLAG_DEFEATED_GIRATINA
	setflag FLAG_HIDE_RYBBEL_PRE_FOREST_GIRATINA
	clearflag FLAG_RYBBEL_GIRATINA_REVEALED
	removeobject LOCALID_RYBBEL_PRE_FOREST_GIRATINA
	call RybbelPreForest_EventScript_RybbelBadgeScene
	return

RybbelPreForest_EventScript_GiratinaGone::
	return

RybbelPreForest_EventScript_BeneathSign::
	msgbox RybbelPreForest_Text_BeneathSign, MSGBOX_SIGN
	end

RybbelPreForest_EventScript_Awakening::
	msgbox RybbelPreForest_Text_RybbelInteresting, MSGBOX_DEFAULT
	msgbox RybbelPreForest_Text_Vortex, MSGBOX_DEFAULT
	fadescreenswapbuffers FADE_TO_WHITE
	delay 30
	fadescreenswapbuffers FADE_FROM_WHITE
	playse SE_M_HYPER_BEAM
	clearflag FLAG_HIDE_RYBBEL_PRE_FOREST_GIRATINA
	addobject LOCALID_RYBBEL_PRE_FOREST_GIRATINA
	setflag FLAG_RYBBEL_GIRATINA_REVEALED
	setflag FLAG_HIDE_RYBBEL_PRE_FOREST_TERMINAL
	removeobject LOCALID_RYBBEL_PRE_FOREST_TERMINAL
	msgbox RybbelPreForest_Text_RybbelGiratina, MSGBOX_DEFAULT
	msgbox RybbelPreForest_Text_RybbelQuestion, MSGBOX_DEFAULT
	applymovement LOCALID_RYBBEL_PRE_FOREST_RYBBEL, RybbelPreForest_Movement_RybbelStepForward
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerFaceDown
	msgbox RybbelPreForest_Text_RybbelBattleSetup, MSGBOX_DEFAULT
	trainerbattle_single TRAINER_RYBBEL_FOREST, RybbelPreForest_Text_RybbelBattleIntro, RybbelPreForest_Text_RybbelBattleDefeat, RybbelPreForest_EventScript_PostBattle
	return

RybbelPreForest_EventScript_PostBattle::
	msgbox RybbelPreForest_Text_RybbelPostBattle, MSGBOX_DEFAULT
	return


RybbelPreForest_EventScript_RybbelBadgeScene::
	call RybbelPreForest_EventScript_MovePlayerToApproach
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerFaceDown
	applymovement LOCALID_RYBBEL_PRE_FOREST_RYBBEL, RybbelPreForest_Movement_RybbelFaceUp
	msgbox RybbelPreForest_Text_RybbelBadgeIntro, MSGBOX_DEFAULT
	goto_if_set FLAG_BADGE07_GET, RybbelPreForest_EventScript_RybbelBadgeScene_After
	setflag FLAG_DEFEATED_MOSSDEEP_GYM
	setflag FLAG_BADGE07_GET
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
RybbelPreForest_EventScript_RybbelBadgeScene_After::
	msgbox RybbelPreForest_Text_RybbelBadgeAfter, MSGBOX_DEFAULT
	applymovement LOCALID_RYBBEL_PRE_FOREST_RYBBEL, RybbelPreForest_Movement_RybbelExitDown
	waitmovement 0
	removeobject LOCALID_RYBBEL_PRE_FOREST_RYBBEL
	setflag FLAG_HIDE_RYBBEL_PRE_FOREST_RYBBEL
	releaseall
	return

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
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerFaceDown
	applymovement LOCALID_RYBBEL_PRE_FOREST_RYBBEL, RybbelPreForest_Movement_RybbelFaceUp
	msgbox RybbelPreForest_Text_RybbelAnalysisA, MSGBOX_DEFAULT
	msgbox RybbelPreForest_Text_RybbelAnalysisB, MSGBOX_DEFAULT
	msgbox RybbelPreForest_Text_RybbelAnalysisC, MSGBOX_DEFAULT
	msgbox RybbelPreForest_Text_RybbelTurnOn, MSGBOX_DEFAULT
	return

RybbelPreForest_EventScript_MovePlayerToApproach::
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerFaceDown
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
	applymovement LOCALID_PLAYER, RybbelPreForest_Movement_PlayerFaceDown
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

RybbelPreForest_Movement_PlayerFaceDown:
	face_down
	step_end

RybbelPreForest_Movement_PlayerFaceRight:
	face_right
	step_end

RybbelPreForest_Movement_RybbelFaceLeft:
	face_left
	step_end

RybbelPreForest_Movement_RybbelFaceUp:
	face_up
	step_end

RybbelPreForest_Movement_RybbelFaceDown:
	face_down
	step_end

RybbelPreForest_Movement_RybbelStepForward:
	walk_left
	walk_up
	face_up
	step_end

RybbelPreForest_Movement_RybbelExitDown:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
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
	.string "Enter the Flag.$"

RybbelPreForest_Text_TerminalWrong:
	.string "ACCESS DENIED.$"

RybbelPreForest_Text_TerminalSuccess:
	.string "Access granted.$"

RybbelPreForest_Text_TerminalAlready:
	.string "The terminal is already unlocked.$"

RybbelPreForest_Text_BeneathSign:
	.string "BENEATH: UkVWM1JTRUlU$"

RybbelPreForest_Text_RybbelInteresting:
	.string "Prof. Rybbel: ...Interesting.\p"
	.string "So you actually managed\nto see beneath the system.$"

RybbelPreForest_Text_Vortex:
	.string "A dark vortex opens above the clearing.\p"
	.string "The air becomes cold.$"

RybbelPreForest_Text_RybbelGiratina:
	.string "Prof. Rybbel: Giratina...\p"
	.string "The ruler of the world beneath ours.\p"
	.string "Seems like your little\nexperiment woke it up.$"

RybbelPreForest_Text_RybbelQuestion:
	.string "Prof. Rybbel: Tell me, {PLAYER}.\p"
	.string "Who deserves the chance\nto face a being like that?\p"
	.string "The one who discovered it?\p"
	.string "Or the one who understands it?$"

RybbelPreForest_Text_RybbelBattleSetup:
	.string "Prof. Rybbel: Let's settle this properly.\p"
	.string "A POKéMON battle.\p"
	.string "Show me what you learned\nbeneath the surface.$"

RybbelPreForest_Text_RybbelBattleIntro:
	.string "Prof. Rybbel: No notes. No safety nets.\p"
	.string "Only analysis.$"

RybbelPreForest_Text_RybbelBattleDefeat:
	.string "Prof. Rybbel: Hah... You overwhelmed me.$"

RybbelPreForest_Text_RybbelPostBattle:
	.string "Prof. Rybbel: Good.\p"
	.string "You earned the right to face whatever\nlies beneath.$"

RybbelPreForest_Text_RybbelBadgeIntro:
	.string "Prof. Rybbel: Haha… impressive.\p"
	.string "I knew you had potential.\p"
	.string "First you reached\nbeneath the system…\p"
	.string "and now you proved it\nin battle as well.\p"
	.string "Most trainers only see\nwhat is in front of them.\p"
	.string "But you… you looked\nbeneath the surface.\p"
	.string "A challenge like this deserves\nmore than just words.\p"
	.string "As professor of cybersecurity…\p"
	.string "This is the Beneath Badge.\p"
	.string "It is given to trainers who know how\nto uncover hidden layers.$"

RybbelPreForest_Text_RybbelBadgeAfter:
	.string "Wear it proudly.\p"
	.string "Remember, {PLAYER}…\p"
	.string "the surface only shows you half the story.\p"
	.string "You've earned it.$"


RybbelPreForest_Text_RybbelPostPrompt:
	.string "Prof. Rybbel: You earned your chance.\p"
	.string "Step forward and face what's waiting.$"
