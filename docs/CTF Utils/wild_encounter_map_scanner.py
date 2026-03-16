#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
CTF Wild Encounter Map Scanner für pokeemerald-expansion

Features:
- scannt Maps aus data/maps
- kann Originalmaps aus dem upstream-Repository ausblenden / ignorieren
- erlaubt individuelles An- und Abwählen per Checkbox
- wertet alle Wild-Encounter-Arten aus (z. B. Land, Wasser, Angeln, Zertrümmerer)
- fasst pro National-Dex-Nummer alles zu einem Eintrag zusammen
- sortiert nach Nationaldex
- kann Ergebnis als TXT oder CSV speichern

Ablage unterhalb des Repos, z. B.:
    docs/CTF Utils/wild_encounter_map_scanner.py

Das Skript sucht das Repository automatisch nach oben hin, kann aber auch mit
--repo <pfad> gestartet werden.
"""

from __future__ import annotations

import argparse
import collections
import csv
import json
import re
import sys
from dataclasses import dataclass
from pathlib import Path

try:
    import tkinter as tk
    from tkinter import filedialog, messagebox, ttk
    from tkinter.scrolledtext import ScrolledText
except Exception:  # pragma: no cover - GUI optional
    tk = None
    filedialog = None
    messagebox = None
    ttk = None
    ScrolledText = None


METHOD_LABELS = {
    "land_mons": "Land",
    "water_mons": "Wasser",
    "rock_smash_mons": "Zertrümmerer",
    "fishing_mons": "Angeln",
}

UPSTREAM_ORIGINAL_MAP_NAMES = frozenset("""
AbandonedShip_CaptainsOffice
AbandonedShip_Corridors_1F
AbandonedShip_Corridors_B1F
AbandonedShip_Deck
AbandonedShip_HiddenFloorCorridors
AbandonedShip_HiddenFloorRooms
AbandonedShip_Room_B1F
AbandonedShip_Rooms2_1F
AbandonedShip_Rooms2_B1F
AbandonedShip_Rooms_1F
AbandonedShip_Rooms_B1F
AbandonedShip_Underwater1
AbandonedShip_Underwater2
AlteringCave
AncientTomb
AquaHideout_1F
AquaHideout_B1F
AquaHideout_B2F
AquaHideout_UnusedRubyMap1
AquaHideout_UnusedRubyMap2
AquaHideout_UnusedRubyMap3
ArtisanCave_1F
ArtisanCave_B1F
BattleColosseum_2P
BattleColosseum_2P_Frlg
BattleColosseum_4P
BattleColosseum_4P_Frlg
BattleFrontier_BattleArenaBattleRoom
BattleFrontier_BattleArenaCorridor
BattleFrontier_BattleArenaLobby
BattleFrontier_BattleDomeBattleRoom
BattleFrontier_BattleDomeCorridor
BattleFrontier_BattleDomeLobby
BattleFrontier_BattleDomePreBattleRoom
BattleFrontier_BattleFactoryBattleRoom
BattleFrontier_BattleFactoryLobby
BattleFrontier_BattleFactoryPreBattleRoom
BattleFrontier_BattlePalaceBattleRoom
BattleFrontier_BattlePalaceCorridor
BattleFrontier_BattlePalaceLobby
BattleFrontier_BattlePikeCorridor
BattleFrontier_BattlePikeLobby
BattleFrontier_BattlePikeRoomFinal
BattleFrontier_BattlePikeRoomNormal
BattleFrontier_BattlePikeRoomWildMons
BattleFrontier_BattlePikeThreePathRoom
BattleFrontier_BattlePyramidFloor
BattleFrontier_BattlePyramidLobby
BattleFrontier_BattlePyramidTop
BattleFrontier_BattleTowerBattleRoom
BattleFrontier_BattleTowerCorridor
BattleFrontier_BattleTowerElevator
BattleFrontier_BattleTowerLobby
BattleFrontier_BattleTowerMultiBattleRoom
BattleFrontier_BattleTowerMultiCorridor
BattleFrontier_BattleTowerMultiPartnerRoom
BattleFrontier_ExchangeServiceCorner
BattleFrontier_Lounge1
BattleFrontier_Lounge2
BattleFrontier_Lounge3
BattleFrontier_Lounge4
BattleFrontier_Lounge5
BattleFrontier_Lounge6
BattleFrontier_Lounge7
BattleFrontier_Lounge8
BattleFrontier_Lounge9
BattleFrontier_Mart
BattleFrontier_OutsideEast
BattleFrontier_OutsideWest
BattleFrontier_PokemonCenter_1F
BattleFrontier_PokemonCenter_2F
BattleFrontier_RankingHall
BattleFrontier_ReceptionGate
BattleFrontier_ScottsHouse
BattlePyramidSquare01
BattlePyramidSquare02
BattlePyramidSquare03
BattlePyramidSquare04
BattlePyramidSquare05
BattlePyramidSquare06
BattlePyramidSquare07
BattlePyramidSquare08
BattlePyramidSquare09
BattlePyramidSquare10
BattlePyramidSquare11
BattlePyramidSquare12
BattlePyramidSquare13
BattlePyramidSquare14
BattlePyramidSquare15
BattlePyramidSquare16
BirthIsland_Exterior
BirthIsland_Exterior_Frlg
BirthIsland_Harbor
BirthIsland_Harbor_Frlg
CaveOfOrigin_1F
CaveOfOrigin_B1F
CaveOfOrigin_Entrance
CaveOfOrigin_UnusedRubySapphireMap1
CaveOfOrigin_UnusedRubySapphireMap2
CaveOfOrigin_UnusedRubySapphireMap3
CeladonCity_Condominiums_1F_Frlg
CeladonCity_Condominiums_2F_Frlg
CeladonCity_Condominiums_3F_Frlg
CeladonCity_Condominiums_RoofRoom_Frlg
CeladonCity_Condominiums_Roof_Frlg
CeladonCity_DepartmentStore_1F_Frlg
CeladonCity_DepartmentStore_2F_Frlg
CeladonCity_DepartmentStore_3F_Frlg
CeladonCity_DepartmentStore_4F_Frlg
CeladonCity_DepartmentStore_5F_Frlg
CeladonCity_DepartmentStore_Elevator_Frlg
CeladonCity_DepartmentStore_Roof_Frlg
CeladonCity_Frlg
CeladonCity_GameCorner_Frlg
CeladonCity_GameCorner_PrizeRoom_Frlg
CeladonCity_Gym_Frlg
CeladonCity_Hotel_Frlg
CeladonCity_House1_Frlg
CeladonCity_PokemonCenter_1F_Frlg
CeladonCity_PokemonCenter_2F_Frlg
CeladonCity_Restaurant_Frlg
CeruleanCave_1F_Frlg
CeruleanCave_2F_Frlg
CeruleanCave_B1F_Frlg
CeruleanCity_BikeShop_Frlg
CeruleanCity_Frlg
CeruleanCity_Gym_Frlg
CeruleanCity_House1_Frlg
CeruleanCity_House2_Frlg
CeruleanCity_House3_Frlg
CeruleanCity_House4_Frlg
CeruleanCity_House5_Frlg
CeruleanCity_Mart_Frlg
CeruleanCity_PokemonCenter_1F_Frlg
CeruleanCity_PokemonCenter_2F_Frlg
CinnabarIsland_Frlg
CinnabarIsland_Gym_Frlg
CinnabarIsland_Mart_Frlg
CinnabarIsland_PokemonCenter_1F_Frlg
CinnabarIsland_PokemonCenter_2F_Frlg
CinnabarIsland_PokemonLab_Entrance_Frlg
CinnabarIsland_PokemonLab_ExperimentRoom_Frlg
CinnabarIsland_PokemonLab_Lounge_Frlg
CinnabarIsland_PokemonLab_ResearchRoom_Frlg
ContestHall
ContestHallBeauty
ContestHallCool
ContestHallCute
ContestHallSmart
ContestHallTough
DesertRuins
DesertUnderpass
DewfordTown
DewfordTown_Gym
DewfordTown_Hall
DewfordTown_House1
DewfordTown_House2
DewfordTown_PokemonCenter_1F
DewfordTown_PokemonCenter_2F
DiglettsCave_B1F_Frlg
DiglettsCave_NorthEntrance_Frlg
DiglettsCave_SouthEntrance_Frlg
EverGrandeCity
EverGrandeCity_ChampionsRoom
EverGrandeCity_DrakesRoom
EverGrandeCity_GlaciasRoom
EverGrandeCity_Hall1
EverGrandeCity_Hall2
EverGrandeCity_Hall3
EverGrandeCity_Hall4
EverGrandeCity_Hall5
EverGrandeCity_HallOfFame
EverGrandeCity_PhoebesRoom
EverGrandeCity_PokemonCenter_1F
EverGrandeCity_PokemonCenter_2F
EverGrandeCity_PokemonLeague_1F
EverGrandeCity_PokemonLeague_2F
EverGrandeCity_SidneysRoom
FallarborTown
FallarborTown_BattleTentBattleRoom
FallarborTown_BattleTentCorridor
FallarborTown_BattleTentLobby
FallarborTown_CozmosHouse
FallarborTown_Mart
FallarborTown_MoveRelearnersHouse
FallarborTown_PokemonCenter_1F
FallarborTown_PokemonCenter_2F
FarawayIsland_Entrance
FarawayIsland_Interior
FieryPath
FiveIsland_Frlg
FiveIsland_Harbor_Frlg
FiveIsland_House1_Frlg
FiveIsland_House2_Frlg
FiveIsland_LostCave_Entrance_Frlg
FiveIsland_LostCave_Room10_Frlg
FiveIsland_LostCave_Room11_Frlg
FiveIsland_LostCave_Room12_Frlg
FiveIsland_LostCave_Room13_Frlg
FiveIsland_LostCave_Room14_Frlg
FiveIsland_LostCave_Room1_Frlg
FiveIsland_LostCave_Room2_Frlg
FiveIsland_LostCave_Room3_Frlg
FiveIsland_LostCave_Room4_Frlg
FiveIsland_LostCave_Room5_Frlg
FiveIsland_LostCave_Room6_Frlg
FiveIsland_LostCave_Room7_Frlg
FiveIsland_LostCave_Room8_Frlg
FiveIsland_LostCave_Room9_Frlg
FiveIsland_Meadow_Frlg
FiveIsland_MemorialPillar_Frlg
FiveIsland_PokemonCenter_1F_Frlg
FiveIsland_PokemonCenter_2F_Frlg
FiveIsland_ResortGorgeous_Frlg
FiveIsland_ResortGorgeous_House_Frlg
FiveIsland_RocketWarehouse_Frlg
FiveIsland_WaterLabyrinth_Frlg
FortreeCity
FortreeCity_DecorationShop
FortreeCity_Gym
FortreeCity_House1
FortreeCity_House2
FortreeCity_House3
FortreeCity_House4
FortreeCity_House5
FortreeCity_Mart
FortreeCity_PokemonCenter_1F
FortreeCity_PokemonCenter_2F
FourIsland_Frlg
FourIsland_Harbor_Frlg
FourIsland_House1_Frlg
FourIsland_House2_Frlg
FourIsland_IcefallCave_1F_Frlg
FourIsland_IcefallCave_B1F_Frlg
FourIsland_IcefallCave_Back_Frlg
FourIsland_IcefallCave_Entrance_Frlg
FourIsland_LoreleisHouse_Frlg
FourIsland_Mart_Frlg
FourIsland_PokemonCenter_1F_Frlg
FourIsland_PokemonCenter_2F_Frlg
FourIsland_PokemonDayCare_Frlg
FuchsiaCity_Frlg
FuchsiaCity_Gym_Frlg
FuchsiaCity_House1_Frlg
FuchsiaCity_House2_Frlg
FuchsiaCity_House3_Frlg
FuchsiaCity_Mart_Frlg
FuchsiaCity_PokemonCenter_1F_Frlg
FuchsiaCity_PokemonCenter_2F_Frlg
FuchsiaCity_SafariZone_Entrance_Frlg
FuchsiaCity_SafariZone_Office_Frlg
FuchsiaCity_WardensHouse_Frlg
GraniteCave_1F
GraniteCave_B1F
GraniteCave_B2F
GraniteCave_StevensRoom
IndigoPlateau_Exterior_Frlg
IndigoPlateau_PokemonCenter_1F_Frlg
IndigoPlateau_PokemonCenter_2F_Frlg
InsideOfTruck
IslandCave
JaggedPass
LavaridgeTown
LavaridgeTown_Gym_1F
LavaridgeTown_Gym_B1F
LavaridgeTown_HerbShop
LavaridgeTown_House
LavaridgeTown_Mart
LavaridgeTown_PokemonCenter_1F
LavaridgeTown_PokemonCenter_2F
LavenderTown_Frlg
LavenderTown_House1_Frlg
LavenderTown_House2_Frlg
LavenderTown_Mart_Frlg
LavenderTown_PokemonCenter_1F_Frlg
LavenderTown_PokemonCenter_2F_Frlg
LavenderTown_VolunteerPokemonHouse_Frlg
LilycoveCity
LilycoveCity_ContestHall
LilycoveCity_ContestLobby
LilycoveCity_CoveLilyMotel_1F
LilycoveCity_CoveLilyMotel_2F
LilycoveCity_DepartmentStoreElevator
LilycoveCity_DepartmentStoreRooftop
LilycoveCity_DepartmentStore_1F
LilycoveCity_DepartmentStore_2F
LilycoveCity_DepartmentStore_3F
LilycoveCity_DepartmentStore_4F
LilycoveCity_DepartmentStore_5F
LilycoveCity_Harbor
LilycoveCity_House1
LilycoveCity_House2
LilycoveCity_House3
LilycoveCity_House4
LilycoveCity_LilycoveMuseum_1F
LilycoveCity_LilycoveMuseum_2F
LilycoveCity_MoveDeletersHouse
LilycoveCity_PokemonCenter_1F
LilycoveCity_PokemonCenter_2F
LilycoveCity_PokemonTrainerFanClub
LilycoveCity_UnusedMart
LittlerootTown
LittlerootTown_BrendansHouse_1F
LittlerootTown_BrendansHouse_2F
LittlerootTown_MaysHouse_1F
LittlerootTown_MaysHouse_2F
LittlerootTown_ProfessorBirchsLab
MagmaHideout_1F
MagmaHideout_2F_1R
MagmaHideout_2F_2R
MagmaHideout_2F_3R
MagmaHideout_3F_1R
MagmaHideout_3F_2R
MagmaHideout_3F_3R
MagmaHideout_4F
MarineCave_End
MarineCave_Entrance
MauvilleCity
MauvilleCity_BikeShop
MauvilleCity_GameCorner
MauvilleCity_Gym
MauvilleCity_House1
MauvilleCity_House2
MauvilleCity_Mart
MauvilleCity_PokemonCenter_1F
MauvilleCity_PokemonCenter_2F
MeteorFalls_1F_1R
MeteorFalls_1F_2R
MeteorFalls_B1F_1R
MeteorFalls_B1F_2R
MeteorFalls_StevensCave
MirageTower_1F
MirageTower_2F
MirageTower_3F
MirageTower_4F
MossdeepCity
MossdeepCity_GameCorner_1F
MossdeepCity_GameCorner_B1F
MossdeepCity_Gym
MossdeepCity_House1
MossdeepCity_House2
MossdeepCity_House3
MossdeepCity_House4
MossdeepCity_Mart
MossdeepCity_PokemonCenter_1F
MossdeepCity_PokemonCenter_2F
MossdeepCity_SpaceCenter_1F
MossdeepCity_SpaceCenter_2F
MossdeepCity_StevensHouse
MtChimney
MtChimney_CableCarStation
MtEmber_Exterior_Frlg
MtEmber_RubyPath_1F_Frlg
MtEmber_RubyPath_B1F_Frlg
MtEmber_RubyPath_B1F_Stairs_Frlg
MtEmber_RubyPath_B2F_Frlg
MtEmber_RubyPath_B2F_Stairs_Frlg
MtEmber_RubyPath_B3F_Frlg
MtEmber_RubyPath_B4F_Frlg
MtEmber_RubyPath_B5F_Frlg
MtEmber_SummitPath_1F_Frlg
MtEmber_SummitPath_2F_Frlg
MtEmber_SummitPath_3F_Frlg
MtEmber_Summit_Frlg
MtMoon_1F_Frlg
MtMoon_B1F_Frlg
MtMoon_B2F_Frlg
MtPyre_1F
MtPyre_2F
MtPyre_3F
MtPyre_4F
MtPyre_5F
MtPyre_6F
MtPyre_Exterior
MtPyre_Summit
NavelRock_1F_Frlg
NavelRock_B1F
NavelRock_B1F_Frlg
NavelRock_BasePath_B10F_Frlg
NavelRock_BasePath_B11F_Frlg
NavelRock_BasePath_B1F_Frlg
NavelRock_BasePath_B2F_Frlg
NavelRock_BasePath_B3F_Frlg
NavelRock_BasePath_B4F_Frlg
NavelRock_BasePath_B5F_Frlg
NavelRock_BasePath_B6F_Frlg
NavelRock_BasePath_B7F_Frlg
NavelRock_BasePath_B8F_Frlg
NavelRock_BasePath_B9F_Frlg
NavelRock_Base_Frlg
NavelRock_Bottom
NavelRock_Down01
NavelRock_Down02
NavelRock_Down03
NavelRock_Down04
NavelRock_Down05
NavelRock_Down06
NavelRock_Down07
NavelRock_Down08
NavelRock_Down09
NavelRock_Down10
NavelRock_Down11
NavelRock_Entrance
NavelRock_Exterior
NavelRock_Exterior_Frlg
NavelRock_Fork
NavelRock_Fork_Frlg
NavelRock_Harbor
NavelRock_Harbor_Frlg
NavelRock_SummitPath_2F_Frlg
NavelRock_SummitPath_3F_Frlg
NavelRock_SummitPath_4F_Frlg
NavelRock_SummitPath_5F_Frlg
NavelRock_Summit_Frlg
NavelRock_Top
NavelRock_Up1
NavelRock_Up2
NavelRock_Up3
NavelRock_Up4
NewMauville_Entrance
NewMauville_Inside
OldaleTown
OldaleTown_House1
OldaleTown_House2
OldaleTown_Mart
OldaleTown_PokemonCenter_1F
OldaleTown_PokemonCenter_2F
OneIsland_Frlg
OneIsland_Harbor_Frlg
OneIsland_House1_Frlg
OneIsland_House2_Frlg
OneIsland_KindleRoad_EmberSpa_Frlg
OneIsland_KindleRoad_Frlg
OneIsland_PokemonCenter_1F_Frlg
OneIsland_PokemonCenter_2F_Frlg
OneIsland_TreasureBeach_Frlg
PacifidlogTown
PacifidlogTown_House1
PacifidlogTown_House2
PacifidlogTown_House3
PacifidlogTown_House4
PacifidlogTown_House5
PacifidlogTown_PokemonCenter_1F
PacifidlogTown_PokemonCenter_2F
PalletTown_Frlg
PalletTown_PlayersHouse_1F_Frlg
PalletTown_PlayersHouse_2F_Frlg
PalletTown_ProfessorOaksLab_Frlg
PalletTown_RivalsHouse_Frlg
PetalburgCity
PetalburgCity_Gym
PetalburgCity_House1
PetalburgCity_House2
PetalburgCity_Mart
PetalburgCity_PokemonCenter_1F
PetalburgCity_PokemonCenter_2F
PetalburgCity_WallysHouse
PetalburgWoods
PewterCity_Frlg
PewterCity_Gym_Frlg
PewterCity_House1_Frlg
PewterCity_House2_Frlg
PewterCity_Mart_Frlg
PewterCity_Museum_1F_Frlg
PewterCity_Museum_2F_Frlg
PewterCity_PokemonCenter_1F_Frlg
PewterCity_PokemonCenter_2F_Frlg
PokemonLeague_AgathasRoom_Frlg
PokemonLeague_BrunosRoom_Frlg
PokemonLeague_ChampionsRoom_Frlg
PokemonLeague_HallOfFame_Frlg
PokemonLeague_LancesRoom_Frlg
PokemonLeague_LoreleisRoom_Frlg
PokemonMansion_1F_Frlg
PokemonMansion_2F_Frlg
PokemonMansion_3F_Frlg
PokemonMansion_B1F_Frlg
PokemonTower_1F_Frlg
PokemonTower_2F_Frlg
PokemonTower_3F_Frlg
PokemonTower_4F_Frlg
PokemonTower_5F_Frlg
PokemonTower_6F_Frlg
PokemonTower_7F_Frlg
PowerPlant_Frlg
RecordCorner
RecordCorner_Frlg
RockTunnel_1F_Frlg
RockTunnel_B1F_Frlg
RocketHideout_B1F_Frlg
RocketHideout_B2F_Frlg
RocketHideout_B3F_Frlg
RocketHideout_B4F_Frlg
RocketHideout_Elevator_Frlg
Route101
Route102
Route103
Route104
Route104_MrBrineysHouse
Route104_PrettyPetalFlowerShop
Route104_Prototype
Route104_PrototypePrettyPetalFlowerShop
Route105
Route106
Route107
Route108
Route109
Route109_SeashoreHouse
Route10_Frlg
Route10_PokemonCenter_1F_Frlg
Route10_PokemonCenter_2F_Frlg
Route110
Route110_SeasideCyclingRoadNorthEntrance
Route110_SeasideCyclingRoadSouthEntrance
Route110_TrickHouseCorridor
Route110_TrickHouseEnd
Route110_TrickHouseEntrance
Route110_TrickHousePuzzle1
Route110_TrickHousePuzzle2
Route110_TrickHousePuzzle3
Route110_TrickHousePuzzle4
Route110_TrickHousePuzzle5
Route110_TrickHousePuzzle6
Route110_TrickHousePuzzle7
Route110_TrickHousePuzzle8
Route111
Route111_OldLadysRestStop
Route111_WinstrateFamilysHouse
Route112
Route112_CableCarStation
Route113
Route113_GlassWorkshop
Route114
Route114_FossilManiacsHouse
Route114_FossilManiacsTunnel
Route114_LanettesHouse
Route115
Route116
Route116_TunnelersRestHouse
Route117
Route117_PokemonDayCare
Route118
Route119
Route119_House
Route119_WeatherInstitute_1F
Route119_WeatherInstitute_2F
Route11_EastEntrance_1F_Frlg
Route11_EastEntrance_2F_Frlg
Route11_Frlg
Route120
Route121
Route121_SafariZoneEntrance
Route122
Route123
Route123_BerryMastersHouse
Route124
Route124_DivingTreasureHuntersHouse
Route125
Route126
Route127
Route128
Route129
Route12_FishingHouse_Frlg
Route12_Frlg
Route12_NorthEntrance_1F_Frlg
Route12_NorthEntrance_2F_Frlg
Route130
Route131
Route132
Route133
Route134
Route13_Frlg
Route14_Frlg
Route15_Frlg
Route15_WestEntrance_1F_Frlg
Route15_WestEntrance_2F_Frlg
Route16_Frlg
Route16_House_Frlg
Route16_NorthEntrance_1F_Frlg
Route16_NorthEntrance_2F_Frlg
Route17_Frlg
Route18_EastEntrance_1F_Frlg
Route18_EastEntrance_2F_Frlg
Route18_Frlg
Route19_Frlg
Route1_Frlg
Route20_Frlg
Route21_North_Frlg
Route21_South_Frlg
Route22_Frlg
Route22_NorthEntrance_Frlg
Route23_Frlg
Route24_Frlg
Route25_Frlg
Route25_SeaCottage_Frlg
Route2_EastBuilding_Frlg
Route2_Frlg
Route2_House_Frlg
Route2_ViridianForest_NorthEntrance_Frlg
Route2_ViridianForest_SouthEntrance_Frlg
Route3_Frlg
Route4_Frlg
Route4_PokemonCenter_1F_Frlg
Route4_PokemonCenter_2F_Frlg
Route5_Frlg
Route5_PokemonDayCare_Frlg
Route5_SouthEntrance_Frlg
Route6_Frlg
Route6_NorthEntrance_Frlg
Route7_EastEntrance_Frlg
Route7_Frlg
Route8_Frlg
Route8_WestEntrance_Frlg
Route9_Frlg
RustboroCity
RustboroCity_CuttersHouse
RustboroCity_DevonCorp_1F
RustboroCity_DevonCorp_2F
RustboroCity_DevonCorp_3F
RustboroCity_Flat1_1F
RustboroCity_Flat1_2F
RustboroCity_Flat2_1F
RustboroCity_Flat2_2F
RustboroCity_Flat2_3F
RustboroCity_Gym
RustboroCity_House1
RustboroCity_House2
RustboroCity_House3
RustboroCity_Mart
RustboroCity_PokemonCenter_1F
RustboroCity_PokemonCenter_2F
RustboroCity_PokemonSchool
RusturfTunnel
SSAnne_1F_Corridor_Frlg
SSAnne_1F_Room1_Frlg
SSAnne_1F_Room2_Frlg
SSAnne_1F_Room3_Frlg
SSAnne_1F_Room4_Frlg
SSAnne_1F_Room5_Frlg
SSAnne_1F_Room6_Frlg
SSAnne_1F_Room7_Frlg
SSAnne_2F_Corridor_Frlg
SSAnne_2F_Room1_Frlg
SSAnne_2F_Room2_Frlg
SSAnne_2F_Room3_Frlg
SSAnne_2F_Room4_Frlg
SSAnne_2F_Room5_Frlg
SSAnne_2F_Room6_Frlg
SSAnne_3F_Corridor_Frlg
SSAnne_B1F_Corridor_Frlg
SSAnne_B1F_Room1_Frlg
SSAnne_B1F_Room2_Frlg
SSAnne_B1F_Room3_Frlg
SSAnne_B1F_Room4_Frlg
SSAnne_B1F_Room5_Frlg
SSAnne_CaptainsOffice_Frlg
SSAnne_Deck_Frlg
SSAnne_Exterior_Frlg
SSAnne_Kitchen_Frlg
SSTidalCorridor
SSTidalLowerDeck
SSTidalRooms
SafariZone_Center_Frlg
SafariZone_Center_RestHouse_Frlg
SafariZone_East_Frlg
SafariZone_East_RestHouse_Frlg
SafariZone_North
SafariZone_North_Frlg
SafariZone_North_RestHouse_Frlg
SafariZone_Northeast
SafariZone_Northwest
SafariZone_RestHouse
SafariZone_SecretHouse_Frlg
SafariZone_South
SafariZone_Southeast
SafariZone_Southwest
SafariZone_West_Frlg
SafariZone_West_RestHouse_Frlg
SaffronCity_Connection_Frlg
SaffronCity_CopycatsHouse_1F_Frlg
SaffronCity_CopycatsHouse_2F_Frlg
SaffronCity_Dojo_Frlg
SaffronCity_Frlg
SaffronCity_Gym_Frlg
SaffronCity_House_Frlg
SaffronCity_Mart_Frlg
SaffronCity_MrPsychicsHouse_Frlg
SaffronCity_PokemonCenter_1F_Frlg
SaffronCity_PokemonCenter_2F_Frlg
SaffronCity_PokemonTrainerFanClub_Frlg
ScorchedSlab
SeafloorCavern_Entrance
SeafloorCavern_Room1
SeafloorCavern_Room2
SeafloorCavern_Room3
SeafloorCavern_Room4
SeafloorCavern_Room5
SeafloorCavern_Room6
SeafloorCavern_Room7
SeafloorCavern_Room8
SeafloorCavern_Room9
SeafoamIslands_1F_Frlg
SeafoamIslands_B1F_Frlg
SeafoamIslands_B2F_Frlg
SeafoamIslands_B3F_Frlg
SeafoamIslands_B4F_Frlg
SealedChamber_InnerRoom
SealedChamber_OuterRoom
SecretBase_BlueCave1
SecretBase_BlueCave2
SecretBase_BlueCave3
SecretBase_BlueCave4
SecretBase_BrownCave1
SecretBase_BrownCave2
SecretBase_BrownCave3
SecretBase_BrownCave4
SecretBase_RedCave1
SecretBase_RedCave2
SecretBase_RedCave3
SecretBase_RedCave4
SecretBase_Shrub1
SecretBase_Shrub2
SecretBase_Shrub3
SecretBase_Shrub4
SecretBase_Tree1
SecretBase_Tree2
SecretBase_Tree3
SecretBase_Tree4
SecretBase_YellowCave1
SecretBase_YellowCave2
SecretBase_YellowCave3
SecretBase_YellowCave4
SevenIsland_Frlg
SevenIsland_Harbor_Frlg
SevenIsland_House_Room1_Frlg
SevenIsland_House_Room2_Frlg
SevenIsland_Mart_Frlg
SevenIsland_PokemonCenter_1F_Frlg
SevenIsland_PokemonCenter_2F_Frlg
SevenIsland_SevaultCanyon_Entrance_Frlg
SevenIsland_SevaultCanyon_Frlg
SevenIsland_SevaultCanyon_House_Frlg
SevenIsland_SevaultCanyon_TanobyKey_Frlg
SevenIsland_TanobyRuins_DilfordChamber_Frlg
SevenIsland_TanobyRuins_Frlg
SevenIsland_TanobyRuins_LiptooChamber_Frlg
SevenIsland_TanobyRuins_MoneanChamber_Frlg
SevenIsland_TanobyRuins_RixyChamber_Frlg
SevenIsland_TanobyRuins_ScufibChamber_Frlg
SevenIsland_TanobyRuins_ViapoisChamber_Frlg
SevenIsland_TanobyRuins_WeepthChamber_Frlg
SevenIsland_TrainerTower_Frlg
ShoalCave_HighTideEntranceRoom
ShoalCave_HighTideInnerRoom
ShoalCave_LowTideEntranceRoom
ShoalCave_LowTideIceRoom
ShoalCave_LowTideInnerRoom
ShoalCave_LowTideLowerRoom
ShoalCave_LowTideStairsRoom
SilphCo_10F_Frlg
SilphCo_11F_Frlg
SilphCo_1F_Frlg
SilphCo_2F_Frlg
SilphCo_3F_Frlg
SilphCo_4F_Frlg
SilphCo_5F_Frlg
SilphCo_6F_Frlg
SilphCo_7F_Frlg
SilphCo_8F_Frlg
SilphCo_9F_Frlg
SilphCo_Elevator_Frlg
SixIsland_AlteringCave_Frlg
SixIsland_DottedHole_1F_Frlg
SixIsland_DottedHole_B1F_Frlg
SixIsland_DottedHole_B2F_Frlg
SixIsland_DottedHole_B3F_Frlg
SixIsland_DottedHole_B4F_Frlg
SixIsland_DottedHole_SapphireRoom_Frlg
SixIsland_Frlg
SixIsland_GreenPath_Frlg
SixIsland_Harbor_Frlg
SixIsland_House_Frlg
SixIsland_Mart_Frlg
SixIsland_OutcastIsland_Frlg
SixIsland_PatternBush_Frlg
SixIsland_PokemonCenter_1F_Frlg
SixIsland_PokemonCenter_2F_Frlg
SixIsland_RuinValley_Frlg
SixIsland_WaterPath_Frlg
SixIsland_WaterPath_House1_Frlg
SixIsland_WaterPath_House2_Frlg
SkyPillar_1F
SkyPillar_2F
SkyPillar_3F
SkyPillar_4F
SkyPillar_5F
SkyPillar_Entrance
SkyPillar_Outside
SkyPillar_Top
SlateportCity
SlateportCity_BattleTentBattleRoom
SlateportCity_BattleTentCorridor
SlateportCity_BattleTentLobby
SlateportCity_Harbor
SlateportCity_House
SlateportCity_Mart
SlateportCity_NameRatersHouse
SlateportCity_OceanicMuseum_1F
SlateportCity_OceanicMuseum_2F
SlateportCity_PokemonCenter_1F
SlateportCity_PokemonCenter_2F
SlateportCity_PokemonFanClub
SlateportCity_SternsShipyard_1F
SlateportCity_SternsShipyard_2F
SootopolisCity
SootopolisCity_Gym_1F
SootopolisCity_Gym_B1F
SootopolisCity_House1
SootopolisCity_House2
SootopolisCity_House3
SootopolisCity_House4
SootopolisCity_House5
SootopolisCity_House6
SootopolisCity_House7
SootopolisCity_LotadAndSeedotHouse
SootopolisCity_Mart
SootopolisCity_MysteryEventsHouse_1F
SootopolisCity_MysteryEventsHouse_B1F
SootopolisCity_PokemonCenter_1F
SootopolisCity_PokemonCenter_2F
SouthernIsland_Exterior
SouthernIsland_Interior
TerraCave_End
TerraCave_Entrance
ThreeIsland_BerryForest_Frlg
ThreeIsland_BondBridge_Frlg
ThreeIsland_DunsparceTunnel_Frlg
ThreeIsland_Frlg
ThreeIsland_Harbor_Frlg
ThreeIsland_House1_Frlg
ThreeIsland_House2_Frlg
ThreeIsland_House3_Frlg
ThreeIsland_House4_Frlg
ThreeIsland_House5_Frlg
ThreeIsland_Mart_Frlg
ThreeIsland_PokemonCenter_1F_Frlg
ThreeIsland_PokemonCenter_2F_Frlg
ThreeIsland_Port_Frlg
TradeCenter
TradeCenter_Frlg
TrainerHill_1F
TrainerHill_2F
TrainerHill_3F
TrainerHill_4F
TrainerHill_Elevator
TrainerHill_Entrance
TrainerHill_Roof
TrainerTower_1F_Frlg
TrainerTower_2F_Frlg
TrainerTower_3F_Frlg
TrainerTower_4F_Frlg
TrainerTower_5F_Frlg
TrainerTower_6F_Frlg
TrainerTower_7F_Frlg
TrainerTower_8F_Frlg
TrainerTower_Elevator_Frlg
TrainerTower_Lobby_Frlg
TrainerTower_Roof_Frlg
TwoIsland_CapeBrink_Frlg
TwoIsland_CapeBrink_House_Frlg
TwoIsland_Frlg
TwoIsland_Harbor_Frlg
TwoIsland_House_Frlg
TwoIsland_JoyfulGameCorner_Frlg
TwoIsland_PokemonCenter_1F_Frlg
TwoIsland_PokemonCenter_2F_Frlg
UndergroundPath_EastEntrance_Frlg
UndergroundPath_EastWestTunnel_Frlg
UndergroundPath_NorthEntrance_Frlg
UndergroundPath_NorthSouthTunnel_Frlg
UndergroundPath_SouthEntrance_Frlg
UndergroundPath_WestEntrance_Frlg
Underwater_MarineCave
Underwater_Route105
Underwater_Route124
Underwater_Route125
Underwater_Route126
Underwater_Route127
Underwater_Route128
Underwater_Route129
Underwater_Route134
Underwater_SeafloorCavern
Underwater_SealedChamber
Underwater_SootopolisCity
UnionRoom
UnionRoom_Frlg
UnusedContestHall1
UnusedContestHall2
UnusedContestHall3
UnusedContestHall4
UnusedContestHall5
UnusedContestHall6
VerdanturfTown
VerdanturfTown_BattleTentBattleRoom
VerdanturfTown_BattleTentCorridor
VerdanturfTown_BattleTentLobby
VerdanturfTown_FriendshipRatersHouse
VerdanturfTown_House
VerdanturfTown_Mart
VerdanturfTown_PokemonCenter_1F
VerdanturfTown_PokemonCenter_2F
VerdanturfTown_WandasHouse
VermilionCity_Frlg
VermilionCity_Gym_Frlg
VermilionCity_House1_Frlg
VermilionCity_House2_Frlg
VermilionCity_House3_Frlg
VermilionCity_Mart_Frlg
VermilionCity_PokemonCenter_1F_Frlg
VermilionCity_PokemonCenter_2F_Frlg
VermilionCity_PokemonFanClub_Frlg
VictoryRoad_1F
VictoryRoad_1F_Frlg
VictoryRoad_2F_Frlg
VictoryRoad_3F_Frlg
VictoryRoad_B1F
VictoryRoad_B2F
ViridianCity_Frlg
ViridianCity_Gym_Frlg
ViridianCity_House_Frlg
ViridianCity_Mart_Frlg
ViridianCity_PokemonCenter_1F_Frlg
ViridianCity_PokemonCenter_2F_Frlg
ViridianCity_School_Frlg
ViridianForest_Frlg
""".strip().splitlines())


@dataclass(frozen=True)
class MapInfo:
    folder: str
    map_id: str
    display_name: str
    is_original: bool
    has_wild_data: bool


@dataclass(frozen=True)
class SpeciesInfo:
    species_const: str
    name: str
    natdex_num: int
    natdex_raw: str


def is_repo_root(path: Path) -> bool:
    return (
        (path / "src/data/wild_encounters.json").is_file()
        and (path / "data/maps").is_dir()
        and (path / "src/data/pokemon/species_info.h").is_file()
        and (path / "include/constants/pokedex.h").is_file()
    )


def find_repo_root(explicit_path: str | None = None) -> Path:
    candidates = []
    if explicit_path:
        candidates.append(Path(explicit_path).expanduser().resolve())

    try:
        candidates.append(Path(__file__).resolve().parent)
    except NameError:
        pass

    candidates.append(Path.cwd().resolve())

    seen = set()
    for candidate in candidates:
        for current in (candidate, *candidate.parents):
            if current in seen:
                continue
            seen.add(current)
            if is_repo_root(current):
                return current

    raise FileNotFoundError(
        "Kein pokeemerald-expansion-Repository gefunden. "
        "Erwartet werden u. a. data/maps und src/data/wild_encounters.json."
    )


def human_method_name(method_key: str) -> str:
    if method_key in METHOD_LABELS:
        return METHOD_LABELS[method_key]
    base = method_key.removesuffix("_mons").replace("_", " ").strip()
    return base.title() if base else method_key


def prettify_species_constant(species_const: str) -> str:
    raw = species_const.removeprefix("SPECIES_").replace("_", " ").lower()
    return " ".join(part.capitalize() for part in raw.split())


def load_wild_encounters(repo_root: Path) -> dict[str, dict[str, set[str]]]:
    path = repo_root / "src/data/wild_encounters.json"
    data = json.loads(path.read_text(encoding="utf-8"))
    result: dict[str, dict[str, set[str]]] = collections.defaultdict(lambda: collections.defaultdict(set))

    for group in data.get("wild_encounter_groups", []):
        if not group.get("for_maps"):
            continue

        for encounter in group.get("encounters", []):
            map_id = encounter.get("map")
            if not map_id:
                continue

            for key, value in encounter.items():
                if not key.endswith("_mons") or not isinstance(value, dict):
                    continue

                for mon in value.get("mons", []):
                    species = mon.get("species")
                    if species and species != "SPECIES_NONE":
                        result[map_id][key].add(species)

    return dict(result)


def parse_natdex_order(repo_root: Path) -> dict[str, int]:
    text = (repo_root / "include/constants/pokedex.h").read_text(encoding="utf-8")
    match = re.search(r"enum\s+NationalDexOrder\s*\{(.*?)\};", text, re.S)
    body = match.group(1) if match else text

    tokens = re.findall(r"\bNATIONAL_DEX_[A-Z0-9_]+\b", body)
    order: dict[str, int] = {}
    for index, token in enumerate(tokens):
        order.setdefault(token, index)
    return order


def parse_species_metadata(repo_root: Path, natdex_order: dict[str, int]) -> dict[str, SpeciesInfo]:
    info_header = (repo_root / "src/data/pokemon/species_info.h").read_text(encoding="utf-8")
    include_files = re.findall(r'#include "species_info/([^"]+)"', info_header)

    result: dict[str, SpeciesInfo] = {}
    split_pattern = re.compile(r"(?=\[SPECIES_[A-Z0-9_]+\]\s*=\s*\{)")
    start_pattern = re.compile(r"\s*\[(SPECIES_[A-Z0-9_]+)\]\s*=\s*\{")
    name_pattern = re.compile(r'\.speciesName\s*=\s*_\("([^"]*)"\)')
    natdex_pattern = re.compile(r"\.natDexNum\s*=\s*([A-Z0-9_]+|\d+)")

    for relative in include_files:
        if relative.startswith("shared_"):
            continue

        path = repo_root / "src/data/pokemon/species_info" / relative
        if not path.is_file():
            continue

        text = path.read_text(encoding="utf-8", errors="ignore")
        for chunk in split_pattern.split(text):
            start_match = start_pattern.match(chunk)
            if not start_match:
                continue

            species_const = start_match.group(1)
            name_match = name_pattern.search(chunk)
            natdex_match = natdex_pattern.search(chunk)

            name = name_match.group(1) if name_match else prettify_species_constant(species_const)
            natdex_raw = natdex_match.group(1) if natdex_match else "NATIONAL_DEX_NONE"
            natdex_num = int(natdex_raw) if natdex_raw.isdigit() else natdex_order.get(natdex_raw, 0)

            result[species_const] = SpeciesInfo(
                species_const=species_const,
                name=name,
                natdex_num=natdex_num,
                natdex_raw=natdex_raw,
            )

    return result


def load_maps(repo_root: Path, encounter_data: dict[str, dict[str, set[str]]]) -> list[MapInfo]:
    maps_dir = repo_root / "data/maps"
    result: list[MapInfo] = []

    for map_json in sorted(maps_dir.glob("*/map.json"), key=lambda p: p.parent.name.casefold()):
        try:
            data = json.loads(map_json.read_text(encoding="utf-8"))
        except json.JSONDecodeError:
            continue

        folder = map_json.parent.name
        map_id = data.get("id", folder)
        display_name = data.get("name", folder)
        result.append(
            MapInfo(
                folder=folder,
                map_id=map_id,
                display_name=display_name,
                is_original=folder in UPSTREAM_ORIGINAL_MAP_NAMES,
                has_wild_data=map_id in encounter_data,
            )
        )

    return result


def build_report_rows(
    selected_map_ids: set[str],
    maps: list[MapInfo],
    encounter_data: dict[str, dict[str, set[str]]],
    species_metadata: dict[str, SpeciesInfo],
) -> list[dict]:
    maps_by_id = {m.map_id: m for m in maps}
    grouped: dict[tuple[str, object], dict] = {}

    for map_id in selected_map_ids:
        methods = encounter_data.get(map_id)
        if not methods:
            continue

        map_info = maps_by_id.get(map_id)
        map_name = map_info.display_name if map_info else map_id

        for method_key, species_set in methods.items():
            method_name = human_method_name(method_key)
            for species_const in species_set:
                meta = species_metadata.get(
                    species_const,
                    SpeciesInfo(
                        species_const=species_const,
                        name=prettify_species_constant(species_const),
                        natdex_num=0,
                        natdex_raw="NATIONAL_DEX_NONE",
                    ),
                )

                group_key = ("natdex", meta.natdex_num) if meta.natdex_num > 0 else ("species", species_const)
                row = grouped.setdefault(
                    group_key,
                    {
                        "natdex_num": meta.natdex_num,
                        "name": meta.name,
                        "species_consts": set(),
                        "map_methods": collections.defaultdict(set),
                    },
                )

                row["species_consts"].add(species_const)
                row["map_methods"][map_name].add(method_name)

                current_name = row["name"]
                if (not current_name) or (len(meta.name) < len(current_name)):
                    row["name"] = meta.name

    rows = []
    for row in grouped.values():
        map_parts = []
        for map_name in sorted(row["map_methods"], key=str.casefold):
            methods = ", ".join(sorted(row["map_methods"][map_name], key=str.casefold))
            map_parts.append(f"{map_name} [{methods}]")

        natdex_num = int(row["natdex_num"])
        dex_label = f"#{natdex_num:04d}" if natdex_num > 0 else "----"

        rows.append(
            {
                "natdex_num": natdex_num,
                "dex_label": dex_label,
                "name": row["name"],
                "species_consts": sorted(row["species_consts"]),
                "map_count": len(row["map_methods"]),
                "locations": map_parts,
                "locations_text": ", ".join(map_parts),
            }
        )

    rows.sort(
        key=lambda item: (
            0 if item["natdex_num"] > 0 else 1,
            item["natdex_num"] if item["natdex_num"] > 0 else 10**9,
            item["name"].casefold(),
        )
    )
    return rows


def format_report_text(rows: list[dict], selected_count: int) -> str:
    if not rows:
        return (
            f"Ausgewählte Maps: {selected_count}\n"
            "Keine wilden Pokémon für die aktuelle Auswahl gefunden."
        )

    lines = [
        f"Ausgewählte Maps: {selected_count}",
        f"Gefundene Pokédex-Einträge: {len(rows)}",
        "",
    ]

    for row in rows:
        lines.append(f"{row['dex_label']} {row['name']}: {row['locations_text']}")

    return "\n".join(lines)


def write_txt(path: Path, text: str) -> None:
    path.write_text(text, encoding="utf-8")


def write_csv(path: Path, rows: list[dict]) -> None:
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle, delimiter=";")
        writer.writerow(["NatDex", "DexLabel", "Pokemon", "MapAnzahl", "Fundorte", "SpeciesKonstanten"])
        for row in rows:
            writer.writerow(
                [
                    row["natdex_num"] or "",
                    row["dex_label"],
                    row["name"],
                    row["map_count"],
                    row["locations_text"],
                    ", ".join(row["species_consts"]),
                ]
            )


def resolve_map_names_to_ids(requested: list[str], maps: list[MapInfo]) -> set[str]:
    by_id = {m.map_id.casefold(): m.map_id for m in maps}
    by_folder = {m.folder.casefold(): m.map_id for m in maps}
    by_name = {m.display_name.casefold(): m.map_id for m in maps}

    result = set()
    for token in requested:
        key = token.casefold()
        map_id = by_id.get(key) or by_folder.get(key) or by_name.get(key)
        if map_id:
            result.add(map_id)
    return result


def run_cli(args: argparse.Namespace) -> int:
    repo_root = find_repo_root(args.repo)
    encounter_data = load_wild_encounters(repo_root)
    natdex_order = parse_natdex_order(repo_root)
    species_metadata = parse_species_metadata(repo_root, natdex_order)
    maps = load_maps(repo_root, encounter_data)

    selected_map_ids: set[str]
    if args.include:
        selected_map_ids = resolve_map_names_to_ids(args.include, maps)
    elif args.custom_only:
        selected_map_ids = {m.map_id for m in maps if not m.is_original}
    else:
        custom_ids = {m.map_id for m in maps if not m.is_original}
        selected_map_ids = custom_ids if custom_ids else {m.map_id for m in maps if m.has_wild_data}

    if args.exclude:
        selected_map_ids -= resolve_map_names_to_ids(args.exclude, maps)

    rows = build_report_rows(selected_map_ids, maps, encounter_data, species_metadata)
    text = format_report_text(rows, len(selected_map_ids))

    if args.txt:
        write_txt(Path(args.txt), text)
    if args.csv:
        write_csv(Path(args.csv), rows)

    print(text)
    return 0


class MapScannerApp:
    def __init__(self, root: tk.Tk, repo_path: str | None = None) -> None:
        self.root = root
        self.root.title("CTF Wild Encounter Map Scanner")

        self.repo_root = find_repo_root(repo_path)
        self.encounter_data = load_wild_encounters(self.repo_root)
        self.natdex_order = parse_natdex_order(self.repo_root)
        self.species_metadata = parse_species_metadata(self.repo_root, self.natdex_order)
        self.maps = load_maps(self.repo_root, self.encounter_data)
        self.maps_by_id = {m.map_id: m for m in self.maps}

        self.map_vars: dict[str, tk.BooleanVar] = {
            m.map_id: tk.BooleanVar(value=False) for m in self.maps
        }

        self.search_var = tk.StringVar()
        self.hide_original_var = tk.BooleanVar(value=False)
        self.only_wild_var = tk.BooleanVar(value=False)
        self.status_var = tk.StringVar()
        self.repo_var = tk.StringVar(value=str(self.repo_root))
        self.last_rows: list[dict] = []
        self.last_text: str = ""

        self._build_ui()
        self._set_initial_selection()
        self._render_map_list()
        self._refresh_report_preview()

    def _build_ui(self) -> None:
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(3, weight=1)
        self.root.rowconfigure(5, weight=2)

        repo_frame = ttk.Frame(self.root, padding=(10, 10, 10, 0))
        repo_frame.grid(row=0, column=0, sticky="ew")
        repo_frame.columnconfigure(1, weight=1)

        ttk.Label(repo_frame, text="Repository:").grid(row=0, column=0, sticky="w")
        ttk.Entry(repo_frame, textvariable=self.repo_var).grid(row=0, column=1, sticky="ew", padx=(6, 6))
        ttk.Button(repo_frame, text="Repo wählen …", command=self._choose_repo).grid(row=0, column=2, sticky="e")

        filter_frame = ttk.Frame(self.root, padding=(10, 10, 10, 0))
        filter_frame.grid(row=1, column=0, sticky="ew")
        filter_frame.columnconfigure(1, weight=1)

        ttk.Label(filter_frame, text="Suche:").grid(row=0, column=0, sticky="w")
        search_entry = ttk.Entry(filter_frame, textvariable=self.search_var)
        search_entry.grid(row=0, column=1, sticky="ew", padx=(6, 12))
        search_entry.bind("<KeyRelease>", lambda _event: self._render_map_list())

        ttk.Checkbutton(
            filter_frame,
            text="Originalmaps ausblenden",
            variable=self.hide_original_var,
            command=self._render_map_list,
        ).grid(row=0, column=2, sticky="w", padx=(0, 12))

        ttk.Checkbutton(
            filter_frame,
            text="Nur Maps mit Wilddaten",
            variable=self.only_wild_var,
            command=self._render_map_list,
        ).grid(row=0, column=3, sticky="w")

        button_frame = ttk.Frame(self.root, padding=(10, 10, 10, 0))
        button_frame.grid(row=2, column=0, sticky="ew")

        ttk.Button(button_frame, text="Alle sichtbaren", command=lambda: self._set_visible_selection(True)).grid(row=0, column=0, padx=(0, 6))
        ttk.Button(button_frame, text="Keine sichtbaren", command=lambda: self._set_visible_selection(False)).grid(row=0, column=1, padx=(0, 6))
        ttk.Button(button_frame, text="Nur Custom", command=self._select_custom_only).grid(row=0, column=2, padx=(0, 6))
        ttk.Button(button_frame, text="Alle mit Wilddaten", command=self._select_wild_only).grid(row=0, column=3, padx=(0, 6))
        ttk.Label(button_frame, textvariable=self.status_var).grid(row=0, column=4, sticky="e", padx=(12, 0))

        list_frame = ttk.LabelFrame(self.root, text="Maps", padding=6)
        list_frame.grid(row=3, column=0, sticky="nsew", padx=10, pady=(10, 0))
        list_frame.columnconfigure(0, weight=1)
        list_frame.rowconfigure(0, weight=1)

        self.canvas = tk.Canvas(list_frame, highlightthickness=0)
        self.canvas.grid(row=0, column=0, sticky="nsew")
        scrollbar = ttk.Scrollbar(list_frame, orient="vertical", command=self.canvas.yview)
        scrollbar.grid(row=0, column=1, sticky="ns")
        self.canvas.configure(yscrollcommand=scrollbar.set)

        self.checkbox_frame = ttk.Frame(self.canvas)
        self.checkbox_window = self.canvas.create_window((0, 0), window=self.checkbox_frame, anchor="nw")

        self.checkbox_frame.bind("<Configure>", self._on_checkbox_frame_configure)
        self.canvas.bind("<Configure>", self._on_canvas_configure)
        self.canvas.bind_all("<MouseWheel>", self._on_mousewheel)

        action_frame = ttk.Frame(self.root, padding=(10, 10, 10, 0))
        action_frame.grid(row=4, column=0, sticky="ew")
        ttk.Button(action_frame, text="Scannen", command=self._refresh_report_preview).grid(row=0, column=0, padx=(0, 6))
        ttk.Button(action_frame, text="TXT speichern …", command=self._save_txt).grid(row=0, column=1, padx=(0, 6))
        ttk.Button(action_frame, text="CSV speichern …", command=self._save_csv).grid(row=0, column=2)

        result_frame = ttk.LabelFrame(self.root, text="Ergebnis", padding=6)
        result_frame.grid(row=5, column=0, sticky="nsew", padx=10, pady=10)
        result_frame.columnconfigure(0, weight=1)
        result_frame.rowconfigure(0, weight=1)

        self.result_box = ScrolledText(result_frame, wrap="word", height=18)
        self.result_box.grid(row=0, column=0, sticky="nsew")

    def _on_checkbox_frame_configure(self, _event=None) -> None:
        self.canvas.configure(scrollregion=self.canvas.bbox("all"))

    def _on_canvas_configure(self, event=None) -> None:
        if event is not None:
            self.canvas.itemconfigure(self.checkbox_window, width=event.width)

    def _on_mousewheel(self, event) -> None:
        try:
            self.canvas.yview_scroll(int(-1 * (event.delta / 120)), "units")
        except Exception:
            pass

    def _choose_repo(self) -> None:
        if filedialog is None:
            return

        selected = filedialog.askdirectory(initialdir=str(self.repo_root))
        if not selected:
            return

        try:
            new_root = find_repo_root(selected)
            self.repo_root = new_root
            self.repo_var.set(str(new_root))
            self.encounter_data = load_wild_encounters(self.repo_root)
            self.natdex_order = parse_natdex_order(self.repo_root)
            self.species_metadata = parse_species_metadata(self.repo_root, self.natdex_order)
            self.maps = load_maps(self.repo_root, self.encounter_data)
            self.maps_by_id = {m.map_id: m for m in self.maps}
            self.map_vars = {m.map_id: tk.BooleanVar(value=False) for m in self.maps}
            self._set_initial_selection()
            self._render_map_list()
            self._refresh_report_preview()
        except Exception as exc:
            if messagebox:
                messagebox.showerror("Fehler", str(exc))

    def _set_initial_selection(self) -> None:
        custom_maps = [m for m in self.maps if not m.is_original]
        default_maps = custom_maps if custom_maps else [m for m in self.maps if m.has_wild_data]

        for m in self.maps:
            self.map_vars[m.map_id].set(m in default_maps)

    def _filtered_maps(self) -> list[MapInfo]:
        query = self.search_var.get().strip().casefold()
        hide_original = self.hide_original_var.get()
        only_wild = self.only_wild_var.get()

        filtered = []
        for m in self.maps:
            if hide_original and m.is_original:
                continue
            if only_wild and not m.has_wild_data:
                continue

            haystack = f"{m.display_name} {m.folder} {m.map_id}".casefold()
            if query and query not in haystack:
                continue
            filtered.append(m)

        return filtered

    def _render_map_list(self) -> None:
        for child in self.checkbox_frame.winfo_children():
            child.destroy()

        filtered = self._filtered_maps()
        for row_index, map_info in enumerate(filtered):
            tags = []
            if not map_info.is_original:
                tags.append("Custom")
            if map_info.has_wild_data:
                tags.append("Wilddaten")
            tag_text = f"  ({' • '.join(tags)})" if tags else ""

            text = f"{map_info.display_name}  [{map_info.map_id}]{tag_text}"
            cb = ttk.Checkbutton(
                self.checkbox_frame,
                text=text,
                variable=self.map_vars[map_info.map_id],
                command=self._update_status_only,
            )
            cb.grid(row=row_index, column=0, sticky="w", pady=1)

        self._update_status_only()
        self._on_checkbox_frame_configure()

    def _update_status_only(self) -> None:
        visible = self._filtered_maps()
        selected_visible = sum(1 for m in visible if self.map_vars[m.map_id].get())
        selected_total = sum(1 for var in self.map_vars.values() if var.get())
        self.status_var.set(
            f"Sichtbar: {len(visible)} | Markiert sichtbar: {selected_visible} | Markiert gesamt: {selected_total}"
        )

    def _set_visible_selection(self, value: bool) -> None:
        for m in self._filtered_maps():
            self.map_vars[m.map_id].set(value)
        self._update_status_only()

    def _select_custom_only(self) -> None:
        for var in self.map_vars.values():
            var.set(False)
        for m in self.maps:
            if not m.is_original:
                self.map_vars[m.map_id].set(True)
        self._update_status_only()

    def _select_wild_only(self) -> None:
        for var in self.map_vars.values():
            var.set(False)
        for m in self.maps:
            if m.has_wild_data:
                self.map_vars[m.map_id].set(True)
        self._update_status_only()

    def _selected_map_ids(self) -> set[str]:
        return {map_id for map_id, var in self.map_vars.items() if var.get()}

    def _refresh_report_preview(self) -> None:
        selected = self._selected_map_ids()
        self.last_rows = build_report_rows(selected, self.maps, self.encounter_data, self.species_metadata)
        self.last_text = format_report_text(self.last_rows, len(selected))

        self.result_box.delete("1.0", "end")
        self.result_box.insert("1.0", self.last_text)
        self._update_status_only()

    def _save_txt(self) -> None:
        self._refresh_report_preview()
        if filedialog is None:
            return

        path = filedialog.asksaveasfilename(
            title="TXT speichern",
            defaultextension=".txt",
            filetypes=[("Textdatei", "*.txt"), ("Alle Dateien", "*.*")],
            initialfile="wild_encounter_report.txt",
        )
        if not path:
            return

        write_txt(Path(path), self.last_text)
        if messagebox:
            messagebox.showinfo("Gespeichert", f"TXT gespeichert:\n{path}")

    def _save_csv(self) -> None:
        self._refresh_report_preview()
        if filedialog is None:
            return

        path = filedialog.asksaveasfilename(
            title="CSV speichern",
            defaultextension=".csv",
            filetypes=[("CSV", "*.csv"), ("Alle Dateien", "*.*")],
            initialfile="wild_encounter_report.csv",
        )
        if not path:
            return

        write_csv(Path(path), self.last_rows)
        if messagebox:
            messagebox.showinfo("Gespeichert", f"CSV gespeichert:\n{path}")


def build_arg_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="Wild-Encounter-Scanner für pokeemerald-expansion")
    parser.add_argument("--repo", help="Pfad zum Repository")
    parser.add_argument("--no-gui", action="store_true", help="ohne GUI im Terminal ausführen")
    parser.add_argument("--custom-only", action="store_true", help="nur Custom-Maps scannen")
    parser.add_argument("--include", nargs="*", help="nur diese Maps scannen (Map-ID, Ordnername oder Anzeigename)")
    parser.add_argument("--exclude", nargs="*", help="diese Maps ausschließen")
    parser.add_argument("--txt", help="TXT-Ausgabe in Datei speichern")
    parser.add_argument("--csv", help="CSV-Ausgabe in Datei speichern")
    return parser


def main() -> int:
    parser = build_arg_parser()
    args = parser.parse_args()

    if args.no_gui or tk is None:
        return run_cli(args)

    root = tk.Tk()
    app = MapScannerApp(root, repo_path=args.repo)
    root.minsize(1000, 750)
    root.mainloop()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
