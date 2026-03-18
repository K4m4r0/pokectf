WasserturmLobby_MapScripts::
    .byte 0


@ =========================================================
@ Pokémon Nurse
@ =========================================================
WasserturmLobby_EventScript_Nurse::
    lock
    faceplayer

    msgbox WasserturmLobby_Text_NurseWelcome, MSGBOX_YESNO
    compare VAR_RESULT, 1
    goto_if 5, WasserturmLobby_EventScript_NurseDecline

    msgbox WasserturmLobby_Text_NurseTakePokemon, MSGBOX_DEFAULT
    closemessage

    special HealPlayerParty
    playfanfare MUS_HEAL
    waitfanfare

    msgbox WasserturmLobby_Text_NurseHealed, MSGBOX_DEFAULT
    release
    end

WasserturmLobby_EventScript_NurseDecline::
    msgbox WasserturmLobby_Text_NurseDecline, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Text
@ =========================================================
WasserturmLobby_Text_NurseWelcome:
    .string "Welcome to our POKéMON CENTER.\p"
    .string "Would you like me to heal your\n"
    .string "POKéMON back to perfect health?$"

WasserturmLobby_Text_NurseTakePokemon:
    .string "Okay, I'll take your POKéMON for a\n"
    .string "few seconds.$"

WasserturmLobby_Text_NurseHealed:
    .string "Thank you for waiting.\p"
    .string "We've restored your POKéMON to\n"
    .string "full health.\p"
    .string "We hope to see you again!$"

WasserturmLobby_Text_NurseDecline:
    .string "We hope to see you again!$"





WasserturmLobby_EventScript_SetBridgeFlag::
    lock
    faceplayer

    goto_if_set FLAG_FLAG8_BRIDGE_SET, WasserturmLobby_BridgeFlag_Already

    setflag FLAG_FLAG8_BRIDGE_SET
    msgbox WasserturmLobby_Text_BridgeFlagSet, MSGBOX_DEFAULT
    release
    end

WasserturmLobby_BridgeFlag_Already:
    msgbox WasserturmLobby_Text_BridgeFlagAlready, MSGBOX_DEFAULT
    release
    end


WasserturmLobby_Text_BridgeFlagSet:
    .string "DEBUG: Bridge flag set.\n"
    .string "Return to the bridge room.$"

WasserturmLobby_Text_BridgeFlagAlready:
    .string "DEBUG: Bridge flag is already set.$"


