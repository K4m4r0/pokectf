EdekaMain_MapScripts::
    .byte 0


@ =========================================================
@ Rock Smash Tool pickup
@ =========================================================
EdekaMain_EventScript_GetRockSmashTool::
    lock
    faceplayer

    goto_if_set FLAG_EDEKAMAIN_GOT_ROCK_SMASH_TOOL, EdekaMain_AlreadyTaken

    msgbox EdekaMain_Text_FoundRockSmashTool, MSGBOX_DEFAULT
    giveitem ITEM_ROCK_SMASH_TOOL, 1
    compare VAR_RESULT, FALSE
    goto_if_eq EdekaMain_BagFull

    setflag FLAG_EDEKAMAIN_GOT_ROCK_SMASH_TOOL
    removeobject LOCALID_ROCK_SMASH_TOOL
    release
    end

EdekaMain_BagFull::
    msgbox EdekaMain_Text_BagFull, MSGBOX_DEFAULT
    release
    end

EdekaMain_AlreadyTaken::
    msgbox EdekaMain_Text_Empty, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Shop
@ =========================================================
EdekaMain_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart EdekaMain_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
EdekaMain_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	pokemartlistend

EdekaMain_EventScript_Karen::
	msgbox EdekaMain_Text_ReviveIsFantastic, MSGBOX_NPC
	end

EdekaMain_EventScript_Nate::
	msgbox EdekaMain_Text_Nate, MSGBOX_NPC
	end

EdekaMain_EventScript_Employee::
	msgbox EdekaMain_Text_NetAndDiveBallsUseful, MSGBOX_NPC
	end

EdekaMain_Text_ReviveIsFantastic:
	.string "KAREN: The YOUTH these days!\p"
	.string "There is this hipster near the\n"
	.string "checkout area telling everyone to\p"
	.string "buy MOO MOO MILK for 33 cents!.\p"
	.string "Lying piece of s#:§!$"

EdekaMain_Text_Nate:
	.string "\"NATE: Yooo, wssup bro.\p"
	.string "Check this out. MOO MOO MILK for\n"
	.string "only 33 cents.\p"
	.string "GIG, goldmine is goated! \"$"

EdekaMain_Text_NetAndDiveBallsUseful:
	.string "EMPLOYEE: Sorry, we are out of\n"
	.string "White Monster.$"


@ =========================================================
@ Text
@ =========================================================
EdekaMain_Text_FoundRockSmashTool:
    .string "You found the ROCK SMASH TOOL!$"

EdekaMain_Text_BagFull:
    .string "Your BAG is full.$"

EdekaMain_Text_Empty:
    .string "There's nothing else here.$"