@ =========================================================
@ Map: KurtHaus
@ File: data/maps/KurtHaus/scripts.pory
@ =========================================================

KurtHaus_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, KurtHaus_OnTransition
    .byte 0

@ Conditions for goto_if (numeric, since NE/NEQ symbols aren't available in your setup)
    .equ CMP_LT, 0
    .equ CMP_EQ, 1
    .equ CMP_GT, 2
    .equ CMP_LE, 3
    .equ CMP_GE, 4
    .equ CMP_NE, 5

@ =========================================================
@ Map transition: After leaving + re-entering, give Celebi once
@ =========================================================
KurtHaus_OnTransition::
    checkflag FLAG_KURT_GS_BALL_TURNED_IN
    compare VAR_RESULT, 1
    goto_if CMP_NE, KurtHaus_OnTransition_End

    checkflag FLAG_KURT_CELEBI_GIVEN
    compare VAR_RESULT, 1
    goto_if CMP_EQ, KurtHaus_OnTransition_End

    lockall
    turnobject LOCALID_KURT, DIR_SOUTH

    msgbox KurtHaus_Text_CelebiReveal, MSGBOX_DEFAULT
    closemessage

    @ Give Celebi with requested stats (includes nickname prompt / party full handling etc.)
    givemon SPECIES_CELEBI, 50, item=ITEM_LEFTOVERS, ball=28, nature=NATURE_MODEST, abilityNum=2, gender=MON_MALE, hpEv=1, atkEv=0, defEv=3, speedEv=50, spAtkEv=50, spDefEv=6, hpIv=7, atkIv=8, defIv=9, speedIv=15, spAtkIv=11, spDefIv=12, move1=MOVE_GIGA_DRAIN, move2=MOVE_PSYCHIC, move3=MOVE_DAZZLING_GLEAM, move4=MOVE_LEAF_STORM, shinyMode=SHINY_MODE_ALWAYS

    @ If your givemon sets VAR_RESULT=0 on failure, don't set the flag (so it can retry)
    compare VAR_RESULT, 0
    goto_if CMP_EQ, KurtHaus_OnTransition_GiveFailed

    setflag FLAG_KURT_CELEBI_GIVEN
    releaseall
    end

KurtHaus_OnTransition_GiveFailed::
    msgbox KurtHaus_Text_NoRoom, MSGBOX_DEFAULT
    releaseall
    end

KurtHaus_OnTransition_End::
    end

@ =========================================================
@ Kurt object interaction (LOCALID_KURT)
@ =========================================================
KurtHaus_EventScript_Kurt::
    lock
    faceplayer

    checkflag FLAG_KURT_CELEBI_GIVEN
    compare VAR_RESULT, 1
    goto_if CMP_EQ, KurtHaus_Kurt_Hello

    checkflag FLAG_KURT_GS_BALL_TURNED_IN
    compare VAR_RESULT, 1
    goto_if CMP_EQ, KurtHaus_Kurt_ComeBackLater

    @ Has GS Ball?
    checkitem ITEM_GS_BALL_2, 1
    compare VAR_RESULT, 0
    goto_if CMP_EQ, KurtHaus_Kurt_Intro

    @ Turn in GS Ball
    msgbox KurtHaus_Text_FoundBall, MSGBOX_DEFAULT
    removeitem ITEM_GS_BALL_2, 1
    setflag FLAG_KURT_GS_BALL_TURNED_IN
    release
    end

KurtHaus_Kurt_Intro::
    msgbox KurtHaus_Text_Intro, MSGBOX_DEFAULT
    release
    end

KurtHaus_Kurt_ComeBackLater::
    msgbox KurtHaus_Text_ComeBackLater, MSGBOX_DEFAULT
    release
    end

KurtHaus_Kurt_Hello::
    msgbox KurtHaus_Text_Hello, MSGBOX_DEFAULT
    release
    end

@ =========================================================
@ Text
@ =========================================================
KurtHaus_Text_Intro:
    .string "My name is Kurt, and I am a\n"
    .string "POKéBALL expert. While I was\n"
    .string "examining a rare ball, TEAM ROCKET\n"
    .string "came and stole it from me.$"

KurtHaus_Text_FoundBall:
    .string "Oh, you found it. That's wonderful.\n"
    .string "I'll examine it right away.\n"
    .string "Please come back later.$"

KurtHaus_Text_ComeBackLater:
    .string "Please come back later.$"

KurtHaus_Text_CelebiReveal:
    .string "The GS Ball contained a very rare\n"
    .string "POKéMON. Please take good care of it.$"

KurtHaus_Text_Hello:
    .string "Hello {PLAYER}, how are you?\n"
    .string "Is CELEBI doing well?$"

KurtHaus_Text_NoRoom:
    .string "Your party and BOXES are full.\n"
    .string "Please make room and come back.$"

