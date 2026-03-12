Flag7_TrickHousePuzzle1_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Flag7_TrickHousePuzzle1_OnLoad
	.byte 0

Flag7_TrickHousePuzzle1_OnLoad:
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_1_STATE, 2, Flag7_TrickHousePuzzle1_EventScript_OpenDoor
	end

Flag7_TrickHousePuzzle1_EventScript_SignPassword123::
	setflag FLAG_TEMP_TRICK_HOUSE_PUZZLE1_PASSWORD123
	msgbox Flag7_TrickHousePuzzle1_Text_SignPassword123, MSGBOX_SIGN
	end

Flag7_TrickHousePuzzle1_EventScript_SignAdmin::
	setflag FLAG_TEMP_TRICK_HOUSE_PUZZLE1_ADMIN
	msgbox Flag7_TrickHousePuzzle1_Text_SignAdmin, MSGBOX_SIGN
	end

Flag7_TrickHousePuzzle1_EventScript_SignComplex::
	setflag FLAG_TEMP_TRICK_HOUSE_PUZZLE1_COMPLEX
	msgbox Flag7_TrickHousePuzzle1_Text_SignComplex, MSGBOX_SIGN
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

Flag7_TrickHousePuzzle1_EventScript_Caretaker::
	trainerbattle_single TRAINER_SALLY, Flag7_TrickHousePuzzle1_Text_CaretakerIntro, Flag7_TrickHousePuzzle1_Text_CaretakerDefeat
	msgbox Flag7_TrickHousePuzzle1_Text_CaretakerPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle1_EventScript_PhDStudent::
	trainerbattle_single TRAINER_ROBIN, Flag7_TrickHousePuzzle1_Text_PhDIntro, Flag7_TrickHousePuzzle1_Text_PhDDefeat
	msgbox Flag7_TrickHousePuzzle1_Text_PhDPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle1_EventScript_Explorer::
	trainerbattle_single TRAINER_EDDIE, Flag7_TrickHousePuzzle1_Text_ExplorerIntro, Flag7_TrickHousePuzzle1_Text_ExplorerDefeat
	msgbox Flag7_TrickHousePuzzle1_Text_ExplorerPostBattle, MSGBOX_AUTOCLOSE
	end

Flag7_TrickHousePuzzle1_Text_CaretakerIntro:
	.string "Hey!\n"
	.string "Students aren't supposed\l"
	.string "to be down here.\p"
	.string "This level contains\n"
	.string "pipes, cables...\p"
	.string "and problems.\p"
	.string "If you want to continue,\n"
	.string "you'll have to get past me.$"

Flag7_TrickHousePuzzle1_Text_CaretakerDefeat:
	.string "Huh...\n"
	.string "Maybe I should let you pass.$"

Flag7_TrickHousePuzzle1_Text_CaretakerPostBattle:
	.string "Anyone who beats me probably\n"
	.string "belongs down here.$"

Flag7_TrickHousePuzzle1_Text_PhDIntro:
	.string "Oh... hi.\p"
	.string "I moved my research office\n"
	.string "down here. It's quiet.\p"
	.string "Also nobody checks\n"
	.string "if I'm actually working.$"

Flag7_TrickHousePuzzle1_Text_PhDDefeat:
	.string "Another failed experiment...$"

Flag7_TrickHousePuzzle1_Text_PhDPostBattle:
	.string "I'll just call it\n"
	.string "Unexpected results.$"

Flag7_TrickHousePuzzle1_Text_ExplorerIntro:
	.string "This place is amazing.\p"
	.string "Hidden tunnels beneath\n"
	.string "the cafeteria!\p"
	.string "Universities always hide\n"
	.string "the coolest stuff underground.\p"
	.string "Want to explore further?\n"
	.string "Beat me first!$"

Flag7_TrickHousePuzzle1_Text_ExplorerDefeat:
	.string "Nice battle!$"

Flag7_TrickHousePuzzle1_Text_ExplorerPostBattle:
	.string "Guess you're a real\n"
	.string "underground explorer too.$"

Flag7_TrickHousePuzzle1_Text_SignPassword123:
	.string "Password: password123$"

Flag7_TrickHousePuzzle1_Text_SignAdmin:
	.string "Password: admin$"

Flag7_TrickHousePuzzle1_Text_SignComplex:
	.string "Password: 8mY1P.C3.V-l$"

Flag7_TrickHousePuzzle1_Text_PasswordPrompt:
	.string "The security console flickers to life.\n"
	.string "Choose a password to enter.$"

Flag7_TrickHousePuzzle1_Text_NoPasswordsKnown:
	.string "You don't recognize any passwords yet.\p"
	.string "Maybe reading more signs will help.$"

Flag7_TrickHousePuzzle1_Text_Password123Warning:
	.string "The system displays a warning:\n"
	.string "“Seriously? This password\p"
	.string "appears in almost\n"
	.string "every breach database. \p"
	.string "Try something less\ny"
	.string "embarrassing.”$"

Flag7_TrickHousePuzzle1_Text_AdminWarning:
	.string "The terminal beeps loudly.\p"
	.string "“Default credentials detected.\p"
	.string "This is exactly how systems\n"
	.string "get compromised.”$"

Flag7_TrickHousePuzzle1_Text_PasswordAccepted:
	.string "“Authentication accepted.”\p"
	.string "The lock clicked open!$"

Flag7_TrickHousePuzzle1_Text_PasswordEntryCancelled:
	.string "The console idles as you step back.$"

Flag7_TrickHousePuzzle1_Text_DoorAlreadyUnlocked:
	.string "The console glows green. The way ahead is\n"
	.string "already open.$"
