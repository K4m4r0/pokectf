Klassenzimmer_Flag7_MapScripts::
    .byte 0
	
Klassenzimmer_Flag7_EventScript_Rybbel::
	lock
	faceplayer
	goto_if_set FLAG_CTF_RYBBEL_CLASS_DONE, Klassenzimmer_Flag7_Rybbel_After

	msgbox Klassenzimmer_Flag7_Text_RybbelIntro, MSGBOX_DEFAULT
	msgbox Klassenzimmer_Flag7_Text_RybbelClass, MSGBOX_DEFAULT
	msgbox Klassenzimmer_Flag7_Text_RybbelFavor, MSGBOX_DEFAULT
	msgbox Klassenzimmer_Flag7_Text_RybbelHelp, MSGBOX_DEFAULT
	msgbox Klassenzimmer_Flag7_Text_RybbelMeet, MSGBOX_DEFAULT
	setflag FLAG_CTF_RYBBEL_CLASS_DONE
	release
	end

Klassenzimmer_Flag7_Rybbel_After::
	msgbox Klassenzimmer_Flag7_Text_RybbelAfter, MSGBOX_DEFAULT
	release
	end

Klassenzimmer_Flag7_Text_RybbelAfter:
	.string "PROF. RYBBEL: I'll be waiting in front\n"
	.string "of the cafeteria. North of the Route\p"
	.string "left from here$"

Klassenzimmer_Flag7_Text_RybbelIntro:
	.string "PROF. RYBBEL: Hmm?\p"
	.string "{PLAYER}?\p"
	.string "That's... unexpected.$"

Klassenzimmer_Flag7_Text_RybbelClass:
	.string "PROF. RYBBEL: This class is supposed\n"
	.string "to be online today.\p"
	.string "Interesting that you\n"
	.string "showed up anyway.$"

Klassenzimmer_Flag7_Text_RybbelFavor:
	.string "PROF. RYBBEL: Actually... that might\n"
	.string "work in my favor.\p"
	.string "I need someone who isn't\n"
	.string "afraid to move around campus.$"

Klassenzimmer_Flag7_Text_RybbelHelp:
	.string "PROF. RYBBEL: If you're willing\n"
	.string "to help,\p"
	.string "meet me in front of\n"
	.string "the cafeteria.\p"
	.string "From here, turn left onto\n"
	.string "LUISENPARK and there head north.$"

Klassenzimmer_Flag7_Text_RybbelMeet:
	.string "PROF. RYBBEL: I have something\n"
	.string "interesting to show you.$"
