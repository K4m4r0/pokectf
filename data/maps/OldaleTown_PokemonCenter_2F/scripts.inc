OldaleTown_PokemonCenter_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CableClub_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, CableClub_OnWarp
	map_script MAP_SCRIPT_ON_LOAD, CableClub_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, CableClub_OnTransition
	.byte 0

@ The below 3 are unused and leftover from RS
OldaleTown_PokemonCenter_2F_EventScript_Colosseum::
	call CableClub_EventScript_Colosseum
	end

OldaleTown_PokemonCenter_2F_EventScript_TradeCenter::
	call CableClub_EventScript_TradeCenter
	end

OldaleTown_PokemonCenter_2F_EventScript_RecordCorner::
	call CableClub_EventScript_RecordCorner
	end




OldaleTown_PokemonCenter_2F_EventScript_GiveCelebi::
	lock
	givemon SPECIES_KYOGRE, 100
	givemon SPECIES_CELEBI, 100, item=ITEM_LEFTOVERS, ball=28, nature=NATURE_MODEST, abilityNum=2, gender=MON_MALE, hpEv=1, atkEv=0, defEv=3, speedEv=50, spAtkEv=50, spDefEv=6, hpIv=7, atkIv=8, defIv=9, speedIv=15, spAtkIv=11, spDefIv=12, move1=MOVE_GIGA_DRAIN, move2=MOVE_PSYCHIC, move3=MOVE_DAZZLING_GLEAM, move4=MOVE_LEAF_STORM
	msgbox OldaleTown_PokemonCenter_2F_Text_GiveCelebi, MSGBOX_DEFAULT
	release
	end


OldaleTown_PokemonCenter_2F_Text_GiveCelebi:
	.string "Received Celebi and Kyogre.$"


