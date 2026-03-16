Testmap_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Testmap_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Testmap_OnFrame
	.byte 0


@ =========================================================
@ First semester reflection scene
@ =========================================================
Testmap_OnTransition::
	goto_if_unset FLAG_DEFEATED_RUSTBORO_GYM, Testmap_OnTransition_End
	goto_if_set FLAG_TESTMAP_FIRST_SEMESTER_SCENE_DONE, Testmap_OnTransition_End

	setvar VAR_TEMP_0, 1
	end

Testmap_OnTransition_End::
	setvar VAR_TEMP_0, 0
	end


Testmap_OnFrame::
	map_script_2 VAR_TEMP_0, 1, Testmap_EventScript_FirstSemesterScene
	.2byte 0


Testmap_EventScript_FirstSemesterScene::
	setvar VAR_TEMP_0, 0
	setflag FLAG_TESTMAP_FIRST_SEMESTER_SCENE_DONE

	lockall

	msgbox Testmap_Text_FirstSemester1, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_PLAYER, Testmap_Movement_FaceLeft
	waitmovement 0
	msgbox Testmap_Text_FirstSemester2, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_PLAYER, Testmap_Movement_FaceRight
	waitmovement 0
	msgbox Testmap_Text_FirstSemester3, MSGBOX_DEFAULT
	closemessage

	msgbox Testmap_Text_FirstSemester4, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_PLAYER, Testmap_Movement_FaceDownJump
	waitmovement 0
	msgbox Testmap_Text_FirstSemester5, MSGBOX_DEFAULT

	releaseall
	end

Testmap_EventScript_TutorialNpc::
	lock
	faceplayer
	goto_if_set FLAG_CTF_TUTORIAL_DONE, Testmap_TutorialNpc_After
	msgbox Testmap_Text_Hint, MSGBOX_DEFAULT
	release
	end

Testmap_TutorialNpc_After:
	msgbox Testmap_Text_After, MSGBOX_DEFAULT
	release
	end

Testmap_EventScript_TutorialTerminal::
	lock
	faceplayer
	goto_if_set FLAG_CTF_TUTORIAL_DONE, Testmap_Terminal_Already

	msgbox Testmap_Text_EnterFlag, MSGBOX_DEFAULT

	setvar VAR_0x8000, 9
	callnative Ctf_FlagTerminal
	waitstate

	compare VAR_RESULT, 1
	goto_if_eq Testmap_Terminal_Ok

	msgbox Testmap_Text_Wrong, MSGBOX_DEFAULT
	release
	end

Testmap_Terminal_Ok:
    msgbox Testmap_Text_Ok, MSGBOX_DEFAULT

    playse SE_BANG
    setvar VAR_0x8004, 1   @ vertical pan
    setvar VAR_0x8005, 1   @ horizontal pan
    setvar VAR_0x8006, 10  @ num shakes
    setvar VAR_0x8007, 2   @ shake delay
    special ShakeCamera
    waitstate
    msgbox Testmap_Text_OkBang, MSGBOX_DEFAULT

    applymovement LOCALID_TESTMAP_BLOCKER, Testmap_Movement_SleepStep
    waitmovement 0

    msgbox Testmap_Text_WokeUp, MSGBOX_DEFAULT

    applymovement LOCALID_TESTMAP_BLOCKER, Testmap_Movement_SleepLeave
    waitmovement 0

    removeobject LOCALID_TESTMAP_BLOCKER
    removeobject LOCALID_TESTMAP_TERMINAL

	setflag FLAG_CTF_TUTORIAL_DONE

    release
    end


Testmap_Terminal_Already:
	msgbox Testmap_Text_Already, MSGBOX_DEFAULT
	release
	end

Testmap_EventScript_BlockNpc::
    lock
    msgbox Testmap_Text_Block, MSGBOX_DEFAULT
    applymovement LOCALID_TESTMAP_BLOCKER, Testmap_Movement_FaceDown
    waitmovement 0
    release
    end

Testmap_Movement_FaceDown:
    face_down
    step_end

Testmap_Movement_SleepStep:
	walk_fast_down
	face_left
	delay_16
	face_right
	delay_16
	step_end


Testmap_Movement_SleepLeave:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Testmap_Movement_FaceLeft:
	face_left
	step_end

Testmap_Movement_FaceRight:
	face_right
	step_end

Testmap_Movement_FaceDownJump:
	face_down
	jump_in_place_down
	step_end

Testmap_EventScript_BlockRoute102::
    goto_if_set FLAG_CTF_GYM1_DEFEATED, Testmap_BlockRoute102_End

    lockall
    msgbox Testmap_Text_GoUniversityFirst, MSGBOX_DEFAULT
    closemessage

    applymovement LOCALID_PLAYER, Testmap_Movement_TurnAndStepRight
    waitmovement 0

    releaseall
	
Testmap_BlockRoute102_End:
	@ Flaggen verstecken NPC für Event auf Route 104, nicht entfernen
	setflag FLAG_HIDE_ROUTE104_OFFICER_M
	setflag FLAG_HIDE_ROUTE104_OFFICER_F
	setflag FLAG_HIDE_ROUTE104_PHONE_CORP_ID
    end

Testmap_Movement_TurnAndStepRight:
    face_right
    walk_right
    step_end

Testmap_Text_GoUniversityFirst:
    .string "I should go to the university first.$"


Testmap_Text_Block:
	.string "This guy is sleeping on the stairs.\n"
	.string "I can't get past him.$"

Testmap_Text_Hint:
	.string "The man sleeps all day. Maybe you can\n" 
	.string "wake him up with a loud BANG?$"

Testmap_Text_After:
	.string "You did it!$"

Testmap_Text_EnterFlag:
	.string "TERMINAL: Enter flag.$"

Testmap_Text_Wrong:
	.string "TERMINAL: Incorrect.$"

Testmap_Text_Ok:
	.string "TERMINAL: Correct.$"

Testmap_Text_OkBang:
	.string "There is a very loud \n BANG coming from the terminal!$"

Testmap_Text_Already:
	.string "TERMINAL: Already cleared.$"

Testmap_Text_WokeUp:
	.string "SLEEPYHEAD: Holy shit!\n"
	.string "What was that?!$"


Testmap_Text_FirstSemester1:
	.string "So that was the first semester.$"

Testmap_Text_FirstSemester2:
	.string "That wasn't so bad.$"

Testmap_Text_FirstSemester3:
	.string "I could go explore the world a bit\n"
	.string "and catch a few more POKéMON.$"

Testmap_Text_FirstSemester4:
	.string "Or I'll go back to university and\n"
	.string "continue with the next course.$"

Testmap_Text_FirstSemester5:
	.string "From now on, that's exactly how it\n"
	.string "works .. did you hear me?!$"

Testmap_EventScript_SignDev::
	msgbox Testmap_Text_DevHouse, MSGBOX_SIGN
	end

Testmap_Text_DevHouse:
	.string "Developer's House\n"
	.string "Currently closed$"




