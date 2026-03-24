BatterieHaus_MapScripts::
	.byte 0


BatterieHaus_EventScript_BatteryNpc::
	lock
	faceplayer

	goto_if_set FLAG_BATTERIEHAUS_GOT_FLASH_TOOL, BatterieHaus_BatteryNpc_After

	checkitem ITEM_BATTERIES, 1
	compare VAR_RESULT, TRUE
	goto_if_eq BatterieHaus_BatteryNpc_HasBatteries

	msgbox BatterieHaus_Text_NoBatteries, MSGBOX_DEFAULT
	release
	end

BatterieHaus_BatteryNpc_HasBatteries:
	setvar VAR_TEMP_0, ITEM_FLASH_TOOL
	checkitemspace VAR_TEMP_0
	goto_if_eq VAR_RESULT, FALSE, BatterieHaus_BatteryNpc_BagFull

	msgbox BatterieHaus_Text_TakeBatteries, MSGBOX_DEFAULT
	closemessage

	removeitem ITEM_BATTERIES, 1
	giveitem ITEM_FLASH_TOOL, 1
	setflag FLAG_BATTERIEHAUS_GOT_FLASH_TOOL

	msgbox BatterieHaus_Text_AfterGive, MSGBOX_DEFAULT
	release
	end

BatterieHaus_BatteryNpc_BagFull:
	msgbox BatterieHaus_Text_BagFull, MSGBOX_DEFAULT
	release
	end

BatterieHaus_BatteryNpc_After:
	msgbox BatterieHaus_Text_Repeat, MSGBOX_DEFAULT
	release
	end


BatterieHaus_Text_TakeBatteries:
	.string "Hey, you've got BATTERIES, great.\n"
	.string "Hand them over!\p"
	.string "Hmm... hmmm... hm\p"
	.string "There, perfect.\n"
	.string "Here, you can keep this.$"

BatterieHaus_Text_AfterGive:
	.string "So, have you discovered anything\n"
	.string "interesting yet?$"

BatterieHaus_Text_Repeat:
	.string "So, have you discovered anything\n"
	.string "interesting yet?$"

BatterieHaus_Text_NoBatteries:
	.string "I've seen a lot on my travels.\p"
	.string "But here, I'm just taking a moment\n"
	.string "to enjoy the view.$"

BatterieHaus_Text_BagFull:
	.string "Looks like your BAG is full.\p"
	.string "Make some space and come back.$"

