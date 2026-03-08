Quadrate_MapScripts::
    .byte 0

    .equ TRAIN_R_X,        8
    .equ TRAIN_R_Y,        11
    .equ TRAIN_R_Y_BELOW,  12

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
    playbgm MUS_CABLE_CAR, TRUE
    applymovement LOCALID_PLAYER,     Quadrate_Train_Movement_SlideRight20
    applymovement LOCALID_ZUGLINKS,   Quadrate_Train_Movement_SlideRight20
    applymovement LOCALID_ZUGRECHTS,  Quadrate_Train_Movement_SlideRight20
    waitmovement 0

    warpsilent MAP_WASSERTURM, 5, 8
    waitstate

    showplayer
    turnobject LOCALID_PLAYER, DIR_NORTH
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

