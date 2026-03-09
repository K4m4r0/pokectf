Abstellkammer_MapScripts::
    .byte 0


@ =========================================================
@ Batteries pickup
@ =========================================================
Abstellkammer_EventScript_GetBatteries::
    lock
    faceplayer

    goto_if_set FLAG_ABSTELLKAMMER_GOT_BATTERIES, Abstellkammer_AlreadyTaken

    msgbox Abstellkammer_Text_FoundBatteries, MSGBOX_DEFAULT
    giveitem ITEM_BATTERIES, 1
    compare VAR_RESULT, FALSE
    goto_if_eq Abstellkammer_BagFull

    setflag FLAG_ABSTELLKAMMER_GOT_BATTERIES
    removeobject LOCALID_BATTERIES
    release
    end

Abstellkammer_BagFull::
    msgbox Abstellkammer_Text_BagFull, MSGBOX_DEFAULT
    release
    end

Abstellkammer_AlreadyTaken::
    msgbox Abstellkammer_Text_Empty, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Text
@ =========================================================
Abstellkammer_Text_FoundBatteries:
    .string "You found some BATTERIES!$"

Abstellkammer_Text_BagFull:
    .string "Your BAG is full.$"

Abstellkammer_Text_Empty:
    .string "There's nothing else here.$"

