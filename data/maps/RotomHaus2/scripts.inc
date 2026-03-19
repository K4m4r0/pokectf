RotomHaus2_MapScripts::
	.byte 0


@ =========================================================
@ Rotom gift for Lemonade
@ =========================================================
RotomHaus2_EventScript_LemonadeForRotom::
	lock
	faceplayer

	goto_if_set FLAG_ROTOMHAUS2_GOT_ROTOM_GIFT, RotomHaus2_LemonadeForRotom_After

	checkitem ITEM_LEMONADE, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RotomHaus2_LemonadeForRotom_HasLemonade

	msgbox RotomHaus2_Text_LemonadeRequest, MSGBOX_DEFAULT
	release
	end

RotomHaus2_LemonadeForRotom_HasLemonade:
	msgbox RotomHaus2_Text_LemonadeAskGive, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RotomHaus2_LemonadeForRotom_End

	removeitem ITEM_LEMONADE, 1

	msgbox RotomHaus2_Text_LemonadeThanks, MSGBOX_DEFAULT
	closemessage

	givemon SPECIES_ROTOM, 20, ITEM_NONE

	setflag FLAG_ROTOMHAUS2_GOT_ROTOM_GIFT

	msgbox RotomHaus2_Text_RotomGift, MSGBOX_DEFAULT
	release
	end

RotomHaus2_LemonadeForRotom_After:
	msgbox RotomHaus2_Text_AfterGift, MSGBOX_DEFAULT
	release
	end

RotomHaus2_LemonadeForRotom_End:
	release
	end


@ =========================================================
@ Text
@ =========================================================
RotomHaus2_Text_LemonadeRequest:
	.string "Oh... it's so warm today.\p"
	.string "I'd really love to have a nice\n"
	.string "LEMONADE right now.$"

RotomHaus2_Text_LemonadeAskGive:
	.string "Is that a LEMONADE?\p"
	.string "Would you give it to me?$"

RotomHaus2_Text_LemonadeThanks:
	.string "Ahh... that's exactly what I needed!\p"
	.string "Thank you so much.$"

RotomHaus2_Text_RotomGift:
	.string "Here, please take this ROTOM.\p"
	.string "It can be a little mischievous,\n"
	.string "but I'm sure it'll like you.$"

RotomHaus2_Text_AfterGift:
	.string "I hope ROTOM is doing well.\p"
	.string "And thanks again for the LEMONADE!$"