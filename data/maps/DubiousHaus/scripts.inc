DubiousHaus_MapScripts::
	.byte 0


@ =========================================================
@ NPC: gives DUBIOUS DISC once if player has Porygon/Porygon2
@ =========================================================
DubiousHaus_EventScript_PorygonFanNpc::
	lock
	faceplayer

	goto_if_set FLAG_DUBIOUS_HAUS_GOT_DUBIOUS_DISC, DubiousHaus_PorygonFan_After

	@ Check for Porygon
	setvar VAR_0x8004, SPECIES_PORYGON
	specialvar VAR_0x8005, Special_PartyContainsSpecies
	compare VAR_0x8005, TRUE
	goto_if_eq DubiousHaus_PorygonFan_GiveItem

	@ Check for Porygon2
	setvar VAR_0x8004, SPECIES_PORYGON2
	specialvar VAR_0x8005, Special_PartyContainsSpecies
	compare VAR_0x8005, TRUE
	goto_if_eq DubiousHaus_PorygonFan_GiveItem

	msgbox DubiousHaus_Text_NoPorygon, MSGBOX_DEFAULT
	release
	end

DubiousHaus_PorygonFan_GiveItem:
	msgbox DubiousHaus_Text_GiveDubiousDisc, MSGBOX_DEFAULT
	giveitem ITEM_DUBIOUS_DISC, 1
	compare VAR_RESULT, FALSE
	goto_if_eq DubiousHaus_PorygonFan_BagFull

	setflag FLAG_DUBIOUS_HAUS_GOT_DUBIOUS_DISC
	release
	end

DubiousHaus_PorygonFan_BagFull:
	msgbox DubiousHaus_Text_BagFull, MSGBOX_DEFAULT
	release
	end

DubiousHaus_PorygonFan_After:
	msgbox DubiousHaus_Text_AfterGift, MSGBOX_DEFAULT
	release
	end


@ =========================================================
@ Porygon object
@ =========================================================
DubiousHaus_EventScript_Porygon::
	lock
	faceplayer
	msgbox DubiousHaus_Text_Porygon, MSGBOX_DEFAULT
	release
	end


@ =========================================================
@ Porygon2 object
@ =========================================================
DubiousHaus_EventScript_Porygon2::
	lock
	faceplayer
	msgbox DubiousHaus_Text_Porygon2, MSGBOX_DEFAULT
	release
	end


@ =========================================================
@ Text
@ =========================================================
DubiousHaus_Text_GiveDubiousDisc:
	.string "Oh, I see you're a fan of the\n"
	.string "PORYGON family too.\p"
	.string "We're pretty rare these days.\p"
	.string "Here, I'm sure you'll find this\n"
	.string "useful.$"

DubiousHaus_Text_AfterGift:
	.string "Hi, how's your PORYGON doing?$"

DubiousHaus_Text_NoPorygon:
	.string "I'm a huge fan of digital POKéMON.\p"
	.string "What do you think of them?$"

DubiousHaus_Text_BagFull:
	.string "Oh! Your BAG is full.\p"
	.string "Come back after making some space.$"

DubiousHaus_Text_Porygon:
	.string "PORYGON stares at you silently.\p"
	.string "It looks like it is buffering an\n"
	.string "emotional response.$"

DubiousHaus_Text_Porygon2:
	.string "PORYGON2 wiggles happily.\p"
	.string "It seems pleased that its latest\n"
	.string "update did not crash.$"

