RotomHaus_MapScripts::
	.byte 0


@ =========================================================
@ Microwave -> Heat Rotom
@ =========================================================
RotomHaus_EventScript_Microwave::
	lock
	faceplayer
	msgbox RotomHaus_Text_Microwave, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RotomHaus_EndRelease

	setvar VAR_0x8005, SPECIES_ROTOM_HEAT
	call RotomHaus_TryChangeSelectedRotom

	release
	end


@ =========================================================
@ Fan -> Fan Rotom
@ =========================================================
RotomHaus_EventScript_Fan::
	lock
	faceplayer
	msgbox RotomHaus_Text_Fan, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RotomHaus_EndRelease

	setvar VAR_0x8005, SPECIES_ROTOM_FAN
	call RotomHaus_TryChangeSelectedRotom

	release
	end


@ =========================================================
@ Fridge -> Frost Rotom
@ =========================================================
RotomHaus_EventScript_Fridge::
	lock
	faceplayer
	msgbox RotomHaus_Text_Fridge, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RotomHaus_EndRelease

	setvar VAR_0x8005, SPECIES_ROTOM_FROST
	call RotomHaus_TryChangeSelectedRotom

	release
	end


@ =========================================================
@ Washer -> Wash Rotom
@ =========================================================
RotomHaus_EventScript_Washer::
	lock
	faceplayer
	msgbox RotomHaus_Text_Washer, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RotomHaus_EndRelease

	setvar VAR_0x8005, SPECIES_ROTOM_WASH
	call RotomHaus_TryChangeSelectedRotom

	release
	end


@ =========================================================
@ Mower -> Mow Rotom
@ =========================================================
RotomHaus_EventScript_Mower::
	lock
	faceplayer
	msgbox RotomHaus_Text_Mower, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RotomHaus_EndRelease

	setvar VAR_0x8005, SPECIES_ROTOM_MOW
	call RotomHaus_TryChangeSelectedRotom

	release
	end


@ =========================================================
@ Old TV -> Base Rotom
@ =========================================================
RotomHaus_EventScript_TV::
	lock
	faceplayer
	msgbox RotomHaus_Text_TV, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RotomHaus_EndRelease

	setvar VAR_0x8005, SPECIES_ROTOM
	call RotomHaus_TryChangeSelectedRotom

	release
	end


@ =========================================================
@ Shared helper
@ VAR_0x8005 = target Rotom species
@ VAR_RESULT from special:
@ 1 = success
@ 2 = selected mon is not Rotom / Rotom form
@ 3 = already in that form
@ 4 = egg
@ =========================================================
RotomHaus_TryChangeSelectedRotom:
	msgbox RotomHaus_Text_ChooseRotom, MSGBOX_DEFAULT
	closemessage

	special ChoosePartyMon
	waitstate

	goto_if_ge VAR_0x8004, PARTY_SIZE, RotomHaus_TryChange_Return

	specialvar VAR_RESULT, Special_RotomHouseChangeSelectedPartyRotomForm

	compare VAR_RESULT, 1
	goto_if_eq RotomHaus_TryChange_Success

	compare VAR_RESULT, 2
	goto_if_eq RotomHaus_TryChange_NotRotom

	compare VAR_RESULT, 3
	goto_if_eq RotomHaus_TryChange_AlreadyForm

	compare VAR_RESULT, 4
	goto_if_eq RotomHaus_TryChange_Egg

	return

RotomHaus_TryChange_Success:
	msgbox RotomHaus_Text_Success, MSGBOX_DEFAULT
	return

RotomHaus_TryChange_NotRotom:
	msgbox RotomHaus_Text_NotRotom, MSGBOX_DEFAULT
	return

RotomHaus_TryChange_AlreadyForm:
	msgbox RotomHaus_Text_AlreadyForm, MSGBOX_DEFAULT
	return

RotomHaus_TryChange_Egg:
	msgbox RotomHaus_Text_Egg, MSGBOX_DEFAULT
	return

RotomHaus_TryChange_Return:
	return


RotomHaus_EndRelease:
	release
	end


@ =========================================================
@ Text
@ =========================================================
RotomHaus_Text_Microwave:
	.string "A microwave oven is humming softly.\p"
	.string "Should ROTOM enter it and change\n"
	.string "into HEAT ROTOM?$"

RotomHaus_Text_Fan:
	.string "A fan is spinning in place.\p"
	.string "Should ROTOM enter it and change\n"
	.string "into FAN ROTOM?$"

RotomHaus_Text_Fridge:
	.string "Cold air leaks from the fridge.\p"
	.string "Should ROTOM enter it and change\n"
	.string "into FROST ROTOM?$"

RotomHaus_Text_Washer:
	.string "The washing machine rattles loudly.\p"
	.string "Should ROTOM enter it and change\n"
	.string "into WASH ROTOM?$"

RotomHaus_Text_Mower:
	.string "A lawn mower is parked here.\p"
	.string "Should ROTOM enter it and change\n"
	.string "into MOW ROTOM?$"

RotomHaus_Text_TV:
	.string "An old TV crackles with static.\p"
	.string "Should ROTOM return to its normal\n"
	.string "form?$"

RotomHaus_Text_ChooseRotom:
	.string "Choose the ROTOM you want to change.$"

RotomHaus_Text_Success:
	.string "ROTOM changed its form!$"

RotomHaus_Text_NotRotom:
	.string "That POKéMON doesn't react to the\n"
	.string "appliance.$"

RotomHaus_Text_AlreadyForm:
	.string "ROTOM is already in that form.$"

RotomHaus_Text_Egg:
	.string "An EGG can't react to the appliance.$"



RotomHaus_EventScript_ExplainHouse::
	lock
	faceplayer
	msgbox RotomHaus_Text_ExplainHouse, MSGBOX_DEFAULT
	release
	end


RotomHaus_Text_ExplainHouse:
	.string "This is the ROTOM HOUSE.\p"
	.string "ROTOM can possess certain household\n"
	.string "appliances and change its form.\p"
	.string "Each machine gives it a different\n"
	.string "appearance and power.\p"
	.string "And that old TV over there?\n"
	.string "It helps ROTOM return to normal.$"

