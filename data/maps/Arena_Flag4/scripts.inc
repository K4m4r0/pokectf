@ Einfach später änderbar in eine andere TM oder anderes Item als Reward für Sieg.
@ Auch Textblock ganz unten nicht vergessen!
#define GYM4_TM ITEM_TM01

Arena_Flag4_MapScripts::
	.byte 0

Arena_Flag4_EventScript_Leader::
	lock
	faceplayer

	@ Schon gewonnen?
	goto_if_set FLAG_BADGE04_GET, Arena_Flag4_After

	msgbox Arena_Flag4_Text_Intro, MSGBOX_DEFAULT

	@ Verlustschutz: kein Whiteout
	setflag B_FLAG_NO_WHITEOUT
	trainerbattle_no_intro TRAINER_ARENA_4, Arena_Flag4_Text_Defeat
	clearflag B_FLAG_NO_WHITEOUT

	@ Check ob verloren
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Arena_Flag4_Lost

	@ Sieg: Badge + Fanfare + TM
	setflag FLAG_BADGE04_GET
	setflag FLAG_DEFEATED_LAVARIDGE_GYM
	setflag FLAG_CTF_GYM4_DEFEATED

	msgbox Arena_Flag4_Text_Win, MSGBOX_DEFAULT
	closemessage

	playfanfare MUS_OBTAIN_BADGE
	msgbox Arena_Flag4_Text_ReceivedBadge, MSGBOX_DEFAULT
	waitfanfare
	closemessage

	giveitem ITEM_TM89, 1
	msgbox Arena_Flag4_Text_TM, MSGBOX_DEFAULT

	release
	end

Arena_Flag4_Lost::
	msgbox Arena_Flag4_Text_Lost, MSGBOX_DEFAULT
	special HealPlayerParty
	release
	end

Arena_Flag4_After::
	msgbox Arena_Flag4_Text_After, MSGBOX_DEFAULT
	release
	end


Arena_Flag4_Text_Intro::
	.string "SANTA: It's time for your exam.\p"
	.string "Show me what you've learned!$"

Arena_Flag4_Text_Defeat::
	.string "SANTA: Correct... enough.$"

Arena_Flag4_Text_Lost::
	.string "SANTA: Not bad, but you need\n"
	.string "to try again.$"

Arena_Flag4_Text_Win::
	.string "SANTA: Excellent!\n"
	.string "You proved yourself worthy.\p"
	.string "Take this, the SCRUM BADGE.$"

Arena_Flag4_Text_ReceivedBadge::
	.string "You received the SCRUM BADGE!$"

Arena_Flag4_Text_TM::
	.string "TM89 contains U-TURN.$"

Arena_Flag4_Text_After::
	.string "SANTA: Our proof is complete.\n"
	.string "Keep studying.$"
