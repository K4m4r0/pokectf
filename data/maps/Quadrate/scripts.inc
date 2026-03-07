Quadrate_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Quadrate_OnTransition
    .byte 0

    .equ TRAIN_R_X,        8
    .equ TRAIN_R_Y,        11
    .equ TRAIN_R_Y_BELOW,  12

Quadrate_OnTransition::
    compare VAR_TRAIN_WARP_STATE, 2
    goto_if 5, Quadrate_OnTransition_End

    setvar VAR_TRAIN_WARP_STATE, 0
    turnobject LOCALID_PLAYER, DIR_SOUTH
    fadescreen FADE_FROM_BLACK
    waitstate
    end

Quadrate_OnTransition_End::
    end


Quadrate_Train_EventScript_Board::
    lockall

    getplayerxy VAR_0x8004, VAR_0x8005
    compare VAR_0x8004, TRAIN_R_X
    goto_if 5, Quadrate_Train_EventScript_WrongSide
    compare VAR_0x8005, TRAIN_R_Y_BELOW
    goto_if 5, Quadrate_Train_EventScript_WrongSide

    msgbox Quadrate_Train_Text_AskTravel, MSGBOX_YESNO
    compare VAR_RESULT, 1
    goto_if 5, Quadrate_Train_EventScript_Cancel
    closemessage

    hideplayer

    applymovement LOCALID_PLAYER,     Quadrate_Train_Movement_SlideRight20
    applymovement LOCALID_ZUGLINKS,   Quadrate_Train_Movement_SlideRight20
    applymovement LOCALID_ZUGRECHTS,  Quadrate_Train_Movement_SlideRight20
    waitmovement 0

    fadescreen FADE_TO_BLACK
    waitstate

    showplayer
    setvar VAR_TRAIN_WARP_STATE, 1
    warp MAP_WASSERTURM, 5, 8
    waitstate

    releaseall
    end

Quadrate_Train_EventScript_WrongSide::
    msgbox Quadrate_Train_Text_WrongSide, MSGBOX_DEFAULT
    releaseall
    end

Quadrate_Train_EventScript_Cancel::
    releaseall
    end


Quadrate_EventScript_LockedTrain::
    msgbox Quadrate_Text_LockedTrainMsg, MSGBOX_SIGN
    end

Quadrate_Officer_EventScript_LockedPassage::
    msgbox Quadrate_Text_LockedPassage, MSGBOX_DEFAULT
    releaseall
    end


Quadrate_Train_Text_AskTravel:
    .string "Do you want to travel\n"
    .string "to the Water Tower?$"

Quadrate_Train_Text_WrongSide:
    .string "The entrance is on the\n"
    .string "south side.$"

Quadrate_Text_LockedTrainMsg:
    .string "The train is not running at the\n"
    .string "moment. Please come back later.$"

Quadrate_Text_LockedPassage:
    .string "We are investigating an incident.\n"
    .string "The passage is closed for the time\p"
    .string "being.$"


Quadrate_Train_Movement_SlideRight20:
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    step_end

