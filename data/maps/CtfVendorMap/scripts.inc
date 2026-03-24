CtfVendorMap_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, CtfVendorMap_OnLoad
    .byte 0

CtfVendorMap_OnLoad::
    callnative CheckConsumeCtfVendorUnlock
    checkflag FLAG_CTF_VENDOR_UNLOCKED
    goto_if TRUE, CtfVendorMap_UnlockTiles
    end

CtfVendorMap_UnlockTiles::
    setmetatile 7, 7, 0x2B0, FALSE
    setmetatile 8, 7, 0x2B0, FALSE
    special DrawWholeMapView
    end


CtfVendor_NpcScript::
    lock
    faceplayer
    callnative CheckConsumeCtfVendorUnlock

    goto_if_eq VAR_RESULT, 2, CtfVendor_NewlyUnlocked
    goto_if_eq VAR_RESULT, 1, CtfVendor_MenuIntro

    msgbox CtfVendor_LockedText, MSGBOX_DEFAULT
    release
    end

CtfVendor_NewlyUnlocked::
    setmetatile 7, 7, 0x2B0, FALSE
    setmetatile 8, 7, 0x2B0, FALSE
    special DrawWholeMapView
    msgbox CtfVendor_UnlockedText, MSGBOX_DEFAULT
    goto CtfVendor_MenuLoop

CtfVendor_MenuIntro::
    msgbox CtfVendor_MenuText, MSGBOX_DEFAULT
    goto CtfVendor_MenuLoop

CtfVendor_MenuLoop::
    multichoice 0, 0, MULTI_CTF_VENDOR_MENU, 1

    goto_if_eq VAR_RESULT, 0, CtfVendor_GiveRareCandy100
    goto_if_eq VAR_RESULT, 1, CtfVendor_Exit

    goto CtfVendor_Exit

CtfVendor_GiveRareCandy100::
    checkitemspace ITEM_RARE_CANDY, 100
    goto_if_eq VAR_RESULT, FALSE, CtfVendor_NoSpaceRareCandy

    additem ITEM_RARE_CANDY, 100
    msgbox CtfVendor_GotRareCandyText, MSGBOX_DEFAULT
    goto CtfVendor_MenuLoop

CtfVendor_NoSpaceRareCandy::
    msgbox CtfVendor_NoSpaceText, MSGBOX_DEFAULT
    release
    end

CtfVendor_Exit::
    release
    end


CtfVendor_LockedText:
    .string "Hey kid, there you are again.\p"
    .string "Do you like your POKéMON?\p"
    .string "To get access to the rest of my\n"
    .string "products, you have to store the\n"
    .string "code word correctly.$"

CtfVendor_UnlockedText:
    .string "You are a smart kid.\p"
    .string "Please enjoy my supplies.$"

CtfVendor_MenuText:
    .string "Take what you need.$"

CtfVendor_GotRareCandyText:
    .string "You received 100 RARE CANDIES.$"

CtfVendor_NoSpaceText:
    .string "Your BAG can't hold 100 more\n"
    .string "RARE CANDIES right now.$"


CtfVendor_HintNpcScript::
    lock
    faceplayer
    msgbox CtfVendor_HintText, MSGBOX_DEFAULT
    release
    end

CtfVendor_HintText:
    .string "Psst, one thousand and one nights.\n"
    .string "You didn't hear that from me.$"

