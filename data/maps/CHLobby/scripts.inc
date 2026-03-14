CHLobby_MapScripts::
    .byte 0


@ =========================================================
@ Challenge House Reception
@ =========================================================
CHLobby_EventScript_Reception::
    lock
    faceplayer

    goto_if_set FLAG_DEFEATED_ELITE_4_DRAKE, CHLobby_Reception_Open

    msgbox CHLobby_Text_ReceptionClosed, MSGBOX_DEFAULT
    release
    end

CHLobby_Reception_Open:
    msgbox CHLobby_Text_ReceptionOpen, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Text
@ =========================================================
CHLobby_Text_ReceptionClosed:
    .string "Welcome to the Challenge House.\p"
    .string "Unfortunately, we're currently\n"
    .string "undergoing renovations.\p"
    .string "Please come back later.$"

CHLobby_Text_ReceptionOpen:
    .string "Welcome to the Challenge House.\p"
    .string "Defeat all our champions and win\n"
    .string "a great prize.$"

