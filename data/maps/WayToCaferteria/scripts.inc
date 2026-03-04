WayToCaferteria_MapScripts::
	.byte 0

WayToCaferteria_EventScript_BusinessStudent::
	lock
	faceplayer
	msgbox WayToCaferteria_Text_BusinessStudent, MSGBOX_DEFAULT
	release
	end

WayToCaferteria_EventScript_DeepForestLakeSign::
	msgbox WayToCaferteria_Text_DeepForestLake, MSGBOX_SIGN
	end

WayToCaferteria_Text_DeepForestLake:
	.string "Deep Forest Lake$"

WayToCaferteria_Text_BusinessStudent:
	.string "Stop. I'm a Business Informatics major, okay?\n"
	.string "And my dad still won't buy me a Porsche.\p"
	.string "Says I have to 'earn it.'\n"
	.string "Unbelievable. Nobody passes.$"
