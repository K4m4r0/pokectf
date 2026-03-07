Wasserturm_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Wasserturm_OnTransition
    .byte 0

Wasserturm_OnTransition::
    compare VAR_TRAIN_WARP_STATE, 1
    goto_if 5, Wasserturm_OnTransition_End

    setvar VAR_TRAIN_WARP_STATE, 0
    turnobject LOCALID_PLAYER, DIR_NORTH
    fadescreen FADE_FROM_BLACK
    waitstate
    end

Wasserturm_OnTransition_End::
    end


Wasserturm_EventScript_ReturnToQuadrate::
    lockall
    fadescreen FADE_TO_BLACK
    waitstate

    setvar VAR_TRAIN_WARP_STATE, 2
    warp MAP_QUADRATE, 8, 12
    waitstate

    releaseall
    end


Wasserturm_Sign::
    lockall
    msgbox Wasserturm_Sign_Text, MSGBOX_DEFAULT
    releaseall
    end

Wasserturm_Sign_Text:
    .string "Old Water Tower$"

