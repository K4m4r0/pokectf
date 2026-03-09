LagerhalleArena_MapScripts::
    .byte 0

@ Vergleichs-Operatoren (numeric, weil NE/NEQ bei dir nicht als Symbol existieren)
    .equ CMP_EQ, 1
    .equ CMP_NE, 5

@ =========================================================
@ Woerner – 3. Arenakampf
@ =========================================================
LagerhalleArena_EventScript_Woerner::
    lock
    faceplayer

    goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, LagerhalleArena_Woerner_AfterBadge

    msgbox LagerhalleArena_Text_Woerner_Intro, MSGBOX_DEFAULT
    closemessage

    trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_16, LagerhalleArena_Text_Woerner_BattleIntro, LagerhalleArena_Text_Woerner_BattleDefeat, LagerhalleArena_EventScript_Woerner_AfterWin
    goto LagerhalleArena_End

LagerhalleArena_EventScript_Woerner_AfterWin::
    msgbox LagerhalleArena_Text_Woerner_Won, MSGBOX_DEFAULT
    closemessage

    setflag FLAG_DEFEATED_MAUVILLE_GYM
    setflag FLAG_BADGE03_GET

    playfanfare MUS_OBTAIN_BADGE
    msgbox LagerhalleArena_Text_Woerner_GaveBadge, MSGBOX_DEFAULT
    waitfanfare
    closemessage

    goto LagerhalleArena_End

LagerhalleArena_Woerner_AfterBadge::
    msgbox LagerhalleArena_Text_Woerner_AfterBadge, MSGBOX_DEFAULT
    goto LagerhalleArena_End

LagerhalleArena_End::
    release
    end

@ =========================================================
@ Text
@ =========================================================
LagerhalleArena_Text_Woerner_Intro:
	.string "Thank you for saving me, that was\n"
	.string "really close. They wanted to force\p"
	.string "me to create an artificial\n"
	.string "POKéMON.\p"
	.string "Well, ... \n"
	.string "that's a topic for another time.\p"
	.string "Let's get started\n"
	.string "with your exam.$"

@ Optional – wird von trainerbattle als “before” Text genutzt (kann auch kurz sein)
LagerhalleArena_Text_Woerner_BattleIntro:
    .string "Show me what you've learned!$"

@ Wird nach dem Sieg im Battle angezeigt (Trainer defeat text)
LagerhalleArena_Text_Woerner_BattleDefeat:
    .string "Well done... You passed.$"

LagerhalleArena_Text_Woerner_Won:
    .string "Excellent work!\n"
    .string "You truly earned the third badge.$"

LagerhalleArena_Text_Woerner_GaveBadge:
	.string "Take good care of your POKéMON.\n"
	.string "Congratulations on passing the\p"
	.string "exam!$"

LagerhalleArena_Text_Woerner_AfterBadge:
    .string "Keep going, {PLAYER}.\p"
    .string "Your CELEBRATION is\n"
	.string "well-deserved!$"

