Klassenzimmer_Flag7_MapScripts::
	.byte 0

Klassenzimmer_Flag7_EventScript_Rybbel::
	lock
	faceplayer
	msgbox Klassenzimmer_Flag7_Text_RybbelIntro, MSGBOX_DEFAULT
	msgbox Klassenzimmer_Flag7_Text_RybbelClass, MSGBOX_DEFAULT
	msgbox Klassenzimmer_Flag7_Text_RybbelFavor, MSGBOX_DEFAULT
	msgbox Klassenzimmer_Flag7_Text_RybbelHelp, MSGBOX_DEFAULT
	msgbox Klassenzimmer_Flag7_Text_RybbelMeet, MSGBOX_DEFAULT
	setflag FLAG_CTF_RYBBEL_CLASS_DONE
	release
	end

Klassenzimmer_Flag7_Text_RybbelIntro:
	.string "Prof. Rybbel: Hmm?\p"
	.string "TRAINER?\p"
	.string "That's... unexpected.$"

Klassenzimmer_Flag7_Text_RybbelClass:
	.string "Prof. Rybbel: This class is supposed\n"
	.string "to be online today.\p"
	.string "Interesting that you\n"
	.string "showed up anyway.$"

Klassenzimmer_Flag7_Text_RybbelFavor:
	.string "Prof. Rybbel: Actually... that might\n"
	.string "work in my favor.\p"
	.string "I need someone who isn't\n"
	.string "afraid to move around campus.$"

Klassenzimmer_Flag7_Text_RybbelHelp:
	.string "Prof. Rybbel: If you're willing\n"
	.string "to help,\p"
	.string "meet me in front of\n"
	.string "the cafeteria.$"

Klassenzimmer_Flag7_Text_RybbelMeet:
	.string "Prof. Rybbel: I have something\n"
	.string "interesting to show you.$"
