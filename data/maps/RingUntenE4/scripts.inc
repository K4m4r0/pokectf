RingUntenE4_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD,       RingUntenE4_OnEnter
    map_script MAP_SCRIPT_ON_TRANSITION, RingUntenE4_OnEnter
    .byte 0

RingUntenE4_OnEnter:
    @ Spy-Objekte immer verstecken
    removeobject LOCALID_CHATOTSPY_A
    removeobject LOCALID_CHATOTSPY_B

    @ Door blocker permanent entfernen, falls unlocked
    goto_if_unset FLAG_RINGUNTENE4_DOOR_UNLOCKED, .LEnd
    removeobject LOCALID_VOICE_DOOR_BLOCKER
.LEnd:
    end


@ =========================================================
@ Object A: Hint object
@ =========================================================
RingUntenE4_EventScript_MurmurHint::
    msgbox RingUntenE4_Text_MurmurHint, MSGBOX_DEFAULT
	closemessage
    end


@ =========================================================
@ Object B: Listening object
@ =========================================================
RingUntenE4_EventScript_ListeningSpot::
    lock
    faceplayer

    @ Already done? (optional)
    goto_if_set FLAG_RINGUNTENE4_CHATOT_HEARD, RingUntenE4_Listening_After

    @ Check if CHATOT is in party (uses your custom special)
    setvar VAR_0x8004, SPECIES_CHATOT
    specialvar VAR_0x8005, Special_PartyContainsSpecies
    compare VAR_0x8005, 1
    goto_if_eq RingUntenE4_Listening_WithChatot

    msgbox RingUntenE4_Text_OnlyMurmuring, MSGBOX_DEFAULT
    release
    end

RingUntenE4_Listening_WithChatot:
    msgbox RingUntenE4_Text_PerhapsChatot, MSGBOX_DEFAULT
    closemessage

    call RingUntenE4_EventScript_ChatotSpySequence

    setflag FLAG_RINGUNTENE4_CHATOT_HEARD
    msgbox RingUntenE4_Text_ChatotOverheard, MSGBOX_DEFAULT
    release
    end

RingUntenE4_Listening_After:
    msgbox RingUntenE4_Text_AfterHeard, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Door blocker at (19,8)
@ =========================================================
RingUntenE4_EventScript_VoiceDoorBlocker::
    lock
    faceplayer

    @ If already unlocked, (should be removed already) but be safe
    goto_if_set FLAG_RINGUNTENE4_DOOR_UNLOCKED, RingUntenE4_Door_After

    @ If not heard yet -> locked message
    goto_if_unset FLAG_RINGUNTENE4_CHATOT_HEARD, RingUntenE4_Door_Locked

    @ Heard already -> unlock
    msgbox RingUntenE4_Text_ImitateVoice, MSGBOX_DEFAULT
    closemessage

    setflag FLAG_RINGUNTENE4_DOOR_UNLOCKED
    removeobject LOCALID_VOICE_DOOR_BLOCKER

    release
    end

RingUntenE4_Door_Locked:
    msgbox RingUntenE4_Text_DoorLocked, MSGBOX_DEFAULT
    release
    end

RingUntenE4_Door_After:
    msgbox RingUntenE4_Text_DoorAlreadyOpen, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Spy sequence (LOCALID_CHATOTSPY)
@ =========================================================
RingUntenE4_EventScript_ChatotSpySequence:
    addobject LOCALID_CHATOTSPY_A
    delay 1
    applymovement LOCALID_CHATOTSPY_A, RingUntenE4_Movement_Chatot_Left3
    waitmovement 0
    removeobject LOCALID_CHATOTSPY_A

    delay 30

    addobject LOCALID_CHATOTSPY_B
    delay 1
    applymovement LOCALID_CHATOTSPY_B, RingUntenE4_Movement_Chatot_Right3
    waitmovement 0
    removeobject LOCALID_CHATOTSPY_B
    return


@ =========================================================
@ Movements
@ =========================================================
RingUntenE4_Movement_Chatot_Left3:
    walk_left
    walk_left
    walk_left
    step_end

RingUntenE4_Movement_Chatot_Right3:
    walk_right
    walk_right
    walk_right
	walk_right
    step_end



@ =========================================================
@ Schilder
@ =========================================================

RingUntenE4_EventScript_SignSeaSideRetreat::
	msgbox RingUntenE4_Text_SeaSideRetreat, MSGBOX_SIGN
	end

RingUntenE4_EventScript_SignRocketOffice::
	msgbox RingUntenE4_Text_RocketOffice, MSGBOX_SIGN
	end


RingUntenE4_Text_SeaSideRetreat:
	.string "Giovanni's Sea Side Retreat$"

RingUntenE4_Text_RocketOffice:
	.string "Team Rocket Branch Office$"
    

@ =========================================================
@ Text
@ =========================================================
RingUntenE4_Text_MurmurHint:
    .string "There is a lot of murmuring coming\n"
    .string "from the upper floors. If only I\p"
    .string "could hear it somehow...$"

RingUntenE4_Text_OnlyMurmuring:
    .string "You only hear loud murmuring.$"

RingUntenE4_Text_PerhapsChatot:
    .string "Perhaps CHATOT can listen in on the\n"
    .string "conversation.$"

RingUntenE4_Text_ChatotOverheard:
    .string "CHATOT overheard the conversation.\n"
    .string "It was just about shopping lists.$"

RingUntenE4_Text_AfterHeard:
    .string "You already know what they talked\n"
    .string "about.$"

RingUntenE4_Text_DoorLocked:
    .string "The door has a voice sensor. Maybe\n"
    .string "you can find something to imitate\p"
    .string "the voice.$"

RingUntenE4_Text_ImitateVoice:
    .string "CHATOT imitates the voice he learned\n"
    .string "from the tower.$"

RingUntenE4_Text_DoorAlreadyOpen:
    .string "The door is unlocked.$"

