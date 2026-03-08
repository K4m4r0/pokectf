Wasserturm_MapScripts::
    .byte 0

Wasserturm_EventScript_ReturnToQuadrate::
    lockall

	playse SE_DOOR
	waitse
    warpsilent MAP_QUADRATE, 8, 12
    waitstate

    turnobject LOCALID_PLAYER, DIR_SOUTH
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

