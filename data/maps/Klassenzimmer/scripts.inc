Klassenzimmer_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Klassenzimmer_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Klassenzimmer_OnFrame
	.byte 0

Klassenzimmer_OnTransition:
	goto_if_set FLAG_CTF_CLASSROOM_INTRO_DONE, Klassenzimmer_OnTransition_AlreadyDone
	setvar VAR_TEMP_0, 0
	end

Klassenzimmer_OnTransition_AlreadyDone:
	setvar VAR_TEMP_0, 1
	end

Klassenzimmer_OnFrame:
	map_script_2 VAR_TEMP_0, 0, Klassenzimmer_EventScript_FirstEntry
	.2byte 0


Klassenzimmer_EventScript_FirstEntry::
	goto_if_set FLAG_CTF_CLASSROOM_INTRO_DONE, Klassenzimmer_FirstEntry_End

	setvar VAR_TEMP_0, 1
	setflag FLAG_CTF_CLASSROOM_INTRO_DONE

	lockall

	turnobject LOCALID_PROF_FARMER, DIR_SOUTH
	turnobject LOCALID_PLAYER, DIR_NORTH

	msgbox Klassenzimmer_Text_Welcome, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_PLAYER, Klassenzimmer_Movement_PlayerToSeat
	waitmovement 0

	msgbox Museum_Text_StudentReceivesMon, MSGBOX_DEFAULT
	closemessage

	givemon SPECIES_SNEASEL, 5, ITEM_RAZOR_CLAW, move1=MOVE_SCRATCH, move2=MOVE_TAUNT, move3=MOVE_LEER, move4=MOVE_THIEF, nature=NATURE_JOLLY, abilityNum=126

	msgbox Klassenzimmer_Text_Museum, MSGBOX_DEFAULT
	closemessage

	setflag FLAG_CTF_MUSEUM_SCENE_PENDING
	setflag FLAG_HIDE_MUSEUM_FLAG1_JESSIE
	setflag FLAG_HIDE_MUSEUM_FLAG1_JAMES
	setflag FLAG_HIDE_MUSEUM_FLAG1_STUDENT

	releaseall
	warpsilent MAP_MUSEUM_FLAG1, 255, 13, 4
	waitstate
	end

Klassenzimmer_FirstEntry_End:
	setvar VAR_TEMP_0, 1
	end


Klassenzimmer_Movement_PlayerToSeat:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	face_up
	step_end


Klassenzimmer_Text_Welcome:
	.string "PROF. FARMER: Ahh {PLAYER},\n"
	.string "we waited especially for you.$"

Klassenzimmer_Text_Museum:
	.string "PROF. FARMER: Today we will visit\n"
	.string "the museum...\p"
	.string "Yesterday, our temporary\n"
	.string "collection was replaced by items\p"
	.string "of ancient history.\p"
	.string "It now contains historical devices\n"
	.string "and calculating machines. Let's\p"
	.string "use this as an\p"
	.string "opportunity to learn something\n"
	.string "new.\p"
	.string "So folks, let's get going.$"

Museum_Text_StudentReceivesMon:
    .string "PROF. FARMER: At the beginning of your\n"
    .string "studies, each student receives a\p"
	.string "SNEASEL, which is intended to support\n"
    .string "you in your learning.\p"
	.string "SNEASEL has been added to your Team.$"


