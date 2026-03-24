OldaleTown_PokemonCenter_caferteria_MapScripts::
	.byte 0


OldaleTown_PokemonCenter_cafeteria_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_CAFETERIA_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

