DHBW_Sued_MapScripts::
	.byte 0


DHBW_Sued_EventScript_Sign::
	msgbox DHBW_Sued_Text_TownSign, MSGBOX_SIGN
	end


DHBW_Sued_Text_TownSign::
	.string "{LEFT_ARROW}EDEKA\n"
	.string "{DOWN_ARROW} NECKARAU$"


DHBW_Sued_EventScript_Girl::
	lockall
	faceplayer
	msgbox DHBW_Sued_Text_Girl, MSGBOX_SIGN
	releaseall
	end

DHBW_Sued_Text_Girl::
	.string "That stupid cliff. Now I can't get\n"
	.string "back to the beach.$"

