Bridgeroom_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD,       Bridgeroom_OnLoad
    map_script MAP_SCRIPT_ON_TRANSITION, Bridgeroom_OnTransition
    .byte 0

Bridgeroom_OnLoad:
    call Bridgeroom_ApplyBridgeIfFlagSet
    end

Bridgeroom_OnTransition:
    call Bridgeroom_ApplyBridgeIfFlagSet
    end

Bridgeroom_ApplyBridgeIfFlagSet:
    goto_if_unset FLAG_FLAG8_BRIDGE_SET, .LBridgeroom_NoBridge
    call Bridgeroom_SetBridgeMetatiles
    special DrawWholeMapView
.LBridgeroom_NoBridge:
    return


Bridgeroom_SetBridgeMetatiles:
    @ Row y = 4
    setmetatile  5, 4, 0x261, FALSE
    setmetatile  6, 4, 0x261, FALSE
    setmetatile  7, 4, 0x261, FALSE
    setmetatile  8, 4, 0x261, FALSE
    setmetatile  9, 4, 0x261, FALSE

    @ Row y = 5
    setmetatile  5, 5, 0x269, FALSE
    setmetatile  6, 5, 0x269, FALSE
    setmetatile  7, 5, 0x269, FALSE
    setmetatile  8, 5, 0x269, FALSE
    setmetatile  9, 5, 0x269, FALSE
    return

Bridgeroom_EventScript_HintNPC::
    lock
    faceplayer
    msgbox Bridgeroom_Text_HintNPC_1, MSGBOX_DEFAULT
    msgbox Bridgeroom_Text_HintNPC_2, MSGBOX_DEFAULT
    release
    end

Bridgeroom_EventScript_Terminal::
    lock
    faceplayer

    goto_if_set FLAG_FLAG8_BRIDGE_SET, Bridgeroom_Terminal_FlagSet

    msgbox Bridgeroom_Text_Terminal_Intro, MSGBOX_DEFAULT
    release
    end


Bridgeroom_Terminal_FlagSet:
    call Bridgeroom_SetBridgeMetatiles
    special DrawWholeMapView
    msgbox Bridgeroom_Text_Terminal_FlagSet, MSGBOX_DEFAULT
    release
    end


Bridgeroom_Text_HintNPC_1:
	.string "This plateau used to have a\n"
	.string "bridge. It only appears if a\p"
	.string "single story flag inside the save\n"
	.string "data is set.$"

Bridgeroom_Text_HintNPC_2:
	.string "If you edited the save but nothing\n"
	.string "changes, you likely patched the\p"
	.string "wrong save copy, or broke a\n"
	.string "section checksum. The game will\p"
	.string "quietly load the other copy.$"

Bridgeroom_Text_Terminal_Intro:
    .string "BRIDGE CONTROL TERMINAL\n"
    .string "Access: OFFLINE\p"
    .string "\n"
	.string "NOTE: This bridge is not\p"
	.string "activated in-game. It requires a\n"
	.string "valid save-state patch.$"

Bridgeroom_Text_Terminal_SaveBlocks:
	.string "Gen-III saves keep TWO game-save\n"
	.string "blocks. Only the one with the\p"
	.string "higher SAVE INDEX is considered\n"
	.string "the newest. If your edit is\p"
	.string "ignored, you may have patched the\n"
	.string "older block.$"

Bridgeroom_Text_Terminal_Sections:
	.string "Each block is split into 4KB\n"
	.string "SECTIONS. At the end of every\p"
	.string "section you can find:\n"
    .string "- Section ID\p"
    .string "- Checksum\n"
    .string "- Signature (bytes: 25 20 01 08)\p"
    .string "- Save Index\n"
    .string "\p"
	.string "Find the right section, then patch\n"
	.string "safely.$"

Bridgeroom_Text_Terminal_Checksum:
	.string "Warning: Section checksums must\n"
	.string "match. Changing even one byte\p"
	.string "without updating the checksum will\n"
	.string "invalidate that section. Tip:\p"
	.string "Flags are bit-packed (8 flags per\n"
	.string "byte). Know your flag ID, then set\p"
	.string "the correct bit.$"

Bridgeroom_Text_Terminal_FlagSet:
    .string "Status: AUTHORIZED\n"
    .string "Bridge tiles deployed.\p"
	.string "If you can read this, your patched\n"
	.string "save was accepted by the game.$"
