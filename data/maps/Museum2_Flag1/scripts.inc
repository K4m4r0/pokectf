@ Einfach später änderbar in eine andere TM oder anderes Item als Reward für Sieg. 
@ Auch Textblock ganz unten nicht vergessen!
#define HEVL_TM ITEM_TM01

Museum2_Flag1_MapScripts::
	.byte 0

Museum2_Flag1_EventScript_Hevl::
	lock
	faceplayer

	@ Schon gewonnen?
	goto_if_set FLAG_BADGE01_GET, Museum2_Flag1_After

	msgbox Museum2_Flag1_Text_Intro, MSGBOX_DEFAULT

	@ Verlustschutz: kein Whiteout
	setflag B_FLAG_NO_WHITEOUT
	trainerbattle_no_intro TRAINER_PROF_HEVL, Museum2_Flag1_Text_Defeat
	clearflag B_FLAG_NO_WHITEOUT

	@ Check ob verloren
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Museum2_Flag1_Lost

	@ Sieg: Badge + Fanfare + TM
	setflag FLAG_BADGE01_GET
	setflag FLAG_CTF_GYM1_DEFEATED
	setflag FLAG_DEFEATED_RUSTBORO_GYM
	clearflag FLAG_EXP_SHARE_GUY
	removeobject LOCALID_BLOCKER

	msgbox Museum2_Flag1_Text_Win, MSGBOX_DEFAULT
	closemessage

	playfanfare MUS_OBTAIN_BADGE
	msgbox Museum2_Flag1_Text_ReceivedBadge, MSGBOX_DEFAULT
	waitfanfare
	closemessage

	giveitem ITEM_TM16, 1
	msgbox Museum2_Flag1_Text_TM, MSGBOX_DEFAULT

	release
	end

Museum2_Flag1_Lost::
	msgbox Museum2_Flag1_Text_Lost, MSGBOX_DEFAULT
	special HealPlayerParty
	release
	end

Museum2_Flag1_After::
	msgbox Museum2_Flag1_Text_After, MSGBOX_DEFAULT
	release
	end


Museum2_Flag1_Text_Intro::
	.string "PROF. HYVEL: You saved the MATHALYZER \n"
	.string "and thus ensured our mathematical\p"
	.string "superiority.\p"
	.string "You can now take your exam with\n"
	.string "me to prove yourself worthy.$"

Museum2_Flag1_Text_Defeat::
	.string "PROF. HYVEL: Correct... enough.$"

Museum2_Flag1_Text_Lost::
	.string "PROF. HYVEL: Not bad, but you need\n"
	.string "to try again.$"

Museum2_Flag1_Text_Win::
	.string "PROF. HYVEL: Excellent!\n"
	.string "You proved yourself worthy.\p"
	.string "Take this, the FIRST BADGE.$"

Museum2_Flag1_Text_ReceivedBadge::
	.string "You received the MATHS BADGE!$"

Museum2_Flag1_Text_TM::
	.string "TM16 contains LIGHT SCREEN.$"

Museum2_Flag1_Text_After::
	.string "PROF. HYVEL: Our proof is complete.\n"
	.string "Keep studying.$"

