Flagroom5_Arena_MapScripts::
    .byte 0

Flagroom5_Arena_EventScript_Leader::
    lock
    faceplayer

    goto_if_set FLAG_DEFEATED_PETALBURG_GYM, Flagroom5_Arena_AfterBadge

    msgbox Flagroom5_Arena_Text_Intro, MSGBOX_DEFAULT
    closemessage

    trainerbattle_single TRAINER_SHIRLEY, Flagroom5_Arena_Text_BattleIntro, Flagroom5_Arena_Text_Defeat, Flagroom5_Arena_EventScript_AfterWin
    goto Flagroom5_Arena_End

Flagroom5_Arena_EventScript_AfterWin::
    msgbox Flagroom5_Arena_Text_Won, MSGBOX_DEFAULT
    closemessage

    setflag FLAG_DEFEATED_PETALBURG_GYM
    setflag FLAG_BADGE05_GET

    playfanfare MUS_OBTAIN_BADGE
    msgbox Flagroom5_Arena_Text_GaveBadge, MSGBOX_DEFAULT
    waitfanfare
    closemessage
    giveitem ITEM_TM57, 1

    goto Flagroom5_Arena_End

Flagroom5_Arena_AfterBadge::
    msgbox Flagroom5_Arena_Text_AfterBadge, MSGBOX_DEFAULT
    goto Flagroom5_Arena_End

Flagroom5_Arena_End::
    release
    end


Flagroom5_Arena_Text_Intro:
    .string "JUDGE: So you found my secret hideout.\n"
    .string "Let's see if you can successfully\p"
    .string "complete the semester.$"

Flagroom5_Arena_Text_BattleIntro:
    .string "JUDGE: Let's begin.$"

Flagroom5_Arena_Text_Defeat:
    .string "JUDGE: Impressive...$"

Flagroom5_Arena_Text_Won:
    .string "JUDGE: Well done!\n"
    .string "You passed the exam.$"

Flagroom5_Arena_Text_GaveBadge:
    .string "JUDGE: Congratulations!\n"
    .string "You've earned the HAWAII BADGE.$"

Flagroom5_Arena_Text_AfterBadge:
    .string "JUDGE: Keep it up, {PLAYER}.$"

