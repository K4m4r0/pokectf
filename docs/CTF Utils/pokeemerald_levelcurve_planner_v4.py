from __future__ import annotations

import csv
import json
import math
import re
from dataclasses import asdict, dataclass, field, fields, is_dataclass
from pathlib import Path
from statistics import mean
from typing import Any, Iterable
from uuid import uuid4
import tkinter as tk
from tkinter import filedialog, messagebox, simpledialog
from tkinter import ttk

APP_TITLE = "pokeemerald-expansion Levelkurven-Planer"
MAX_TEAM_SIZE = 6
GROWTH_RATES = [
    "Erratic",
    "Fast",
    "Medium Fast",
    "Medium Slow",
    "Slow",
    "Fluctuating",
]
PRESETS = [
    "pokeemerald-expansion modern",
    "Emerald / Gen 3",
    "Benutzerdefiniert",
]
CANONICAL_VANILLA_MAPS = {
    "AbandonedShip_CaptainsOffice", "AbandonedShip_Corridors_1F", "AbandonedShip_Corridors_B1F", "AbandonedShip_Corridors_B2F",
    "AbandonedShip_Deck", "AbandonedShip_HiddenFloorCorridors", "AbandonedShip_HiddenFloorRooms", "AbandonedShip_Rooms_1F",
    "AbandonedShip_Rooms2_1F", "AbandonedShip_Room_B1F", "AbandonedShip_Room_B2F", "AbandonedShip_Underwater1", "AbandonedShip_Underwater2",
    "ArtisanCave_1F", "ArtisanCave_B1F", "BattleColosseum_2P", "BattleColosseum_4P", "BattleDome", "BattleDome_Corridor",
    "BattleFactory", "BattleFactory_PreBattleRoom", "BattleFrontier_BattlePointExchangeServiceCorner", "BattleFrontier_BattleTowerLobby",
    "BattleFrontier_BattleTowerMultiBattleRoom", "BattleFrontier_BattleTowerOutsideWest", "BattleFrontier_BattleTower_Rooftop", "BattleFrontier_BattleTower_TeleporterRoom",
    "BattleFrontier_BattleTower_WaterRoom", "BattleFrontier_BattleTower_WaterRoom2", "BattleFrontier_DomeLobby", "BattleFrontier_East",
    "BattleFrontier_ExchangeServiceCorner", "BattleFrontier_Lounge1", "BattleFrontier_Lounge2", "BattleFrontier_Mart", "BattleFrontier_OutsideEast",
    "BattleFrontier_OutsideWest", "BattleFrontier_PokemonCenter_1F", "BattleFrontier_PokemonCenter_2F", "BattleFrontier_RankingHall", "BattleFrontier_ReceptionGate",
    "BattleFrontier_ScottQuarters", "BattleFrontier_Southwest", "BattleFrontier_SwapShop", "BattleFrontier_TowerLobby", "BattleFrotier_BattlePikeCorridor",
    "BattleFrontier_BattlePikeLobby", "BattleFrontier_BattlePikeRoomFinal", "BattleFrontier_BattlePikeThreePathRoom", "BattleFrontier_BattlePyramidEmptySquare",
    "BattleFrontier_BattlePyramidFloor", "BattleFrontier_BattlePyramidLobby", "BattleFrontier_BattlePyramidSquare01", "BattleFrontier_BattlePyramidSquare02",
    "BattleFrontier_BattlePyramidSquare03", "BattleFrontier_BattlePyramidSquare04", "BattleFrontier_BattlePyramidSquare05", "BattleFrontier_BattlePyramidSquare06",
    "BattleFrontier_BattlePyramidSquare07", "BattleFrontier_BattlePyramidSquare08", "BattleFrontier_BattlePyramidSquare09", "BattleFrontier_BattlePyramidSquare10",
    "BattleFrontier_BattlePyramidSquare11", "BattleFrontier_BattlePyramidSquare12", "BattleFrontier_BattlePyramidSquare13", "BattleFrontier_BattlePyramidSquare14",
    "BattleFrontier_BattlePyramidSquare15", "BattleFrontier_BattlePyramidSquare16", "BattleFrontier_BattlePyramidSquare17", "BattleFrontier_BattlePyramidSquare18",
    "BattleFrontier_BattlePyramidSquare19", "BattleFrontier_BattlePyramidSquare20", "BattleFrontier_BattlePyramidSquare21", "BattleFrontier_BattlePyramidSquare22",
    "BattleFrontier_BattlePyramidSquare23", "BattleFrontier_BattlePyramidSquare24", "BattleFrontier_BattlePyramidSquare25", "BattleFrontier_BattlePyramidSquare26",
    "BattleFrontier_BattlePyramidSquare27", "BattleFrontier_BattlePyramidSquare28", "BattleFrontier_BattlePyramidSquare29", "BattleFrontier_BattlePyramidSquare30",
    "BattleFrontier_BattlePyramidSquare31", "BattleFrontier_BattlePyramidSquare32", "BattleFrontier_BattlePyramidSquare33", "BattleFrontier_BattlePyramidSquare34",
    "BattleFrontier_BattlePyramidSquare35", "BattleFrontier_BattlePyramidSquare36", "BattleFrontier_BattlePyramidSquare37", "BattleFrontier_BattlePyramidSquare38",
    "BattleFrontier_BattlePyramidSquare39", "BattleFrontier_BattlePyramidSquare40", "BattleFrontier_BattlePyramidSquare41", "BattleFrontier_BattlePyramidSquare42",
    "BattleFrontier_BattlePyramidSquare43", "BattleFrontier_BattlePyramidSquare44", "BattleFrontier_BattlePyramidSquare45", "BattleFrontier_BattlePyramidSquare46",
    "BattleFrontier_BattlePyramidSquare47", "BattleFrontier_BattlePyramidSquare48", "BattleFrontier_BattlePyramidSquare49", "BattleFrontier_BattlePyramidSquare50",
    "BattleFrontier_BattlePyramidSquare51", "BattleFrontier_BattlePyramidSquare52", "BattleFrontier_BattlePyramidSquare53", "BattleFrontier_BattlePyramidSquare54",
    "BattleFrontier_BattlePyramidSquare55", "BattleFrontier_BattlePyramidSquare56", "BattleFrontier_BattlePyramidSquare57", "BattleFrontier_BattlePyramidSquare58",
    "BattleFrontier_BattlePyramidSquare59", "BattleFrontier_BattlePyramidSquare60", "BattleFrontier_BattlePyramidSquare61", "BattleFrontier_BattlePyramidSquare62",
    "BattleFrontier_BattlePyramidSquare63", "BattleFrontier_BattlePyramidSquare64", "BattleFrontier_BattlePyramidSquare65", "BattleFrontier_BattlePyramidSquare66",
    "BattleFrontier_BattlePyramidSquare67", "BattleFrontier_BattlePyramidSquare68", "BattleFrontier_BattlePyramidSquare69", "BattleFrontier_BattlePyramidSquare70",
    "BattleFrontier_BattlePyramidSquare71", "BattleFrontier_BattlePyramidSquare72", "BattleFrontier_BattlePyramidSquare73", "BattleFrontier_BattlePyramidSquare74",
    "BattleFrontier_BattlePyramidSquare75", "BattleFrontier_BattlePyramidSquare76", "BattleFrontier_BattlePyramidSquare77", "BattleFrontier_BattlePyramidSquare78",
    "BattleFrontier_BattlePyramidSquare79", "BattleFrontier_BattlePyramidSquare80", "BattleFrontier_BattlePyramidSquare81", "BattleFrontier_BattlePyramidSquare82",
    "BattleFrontier_BattlePyramidSquare83", "BattleFrontier_BattlePyramidSquare84", "BattleFrontier_BattlePyramidSquare85", "BattleFrontier_BattlePyramidSquare86",
    "BattleFrontier_BattlePyramidSquare87", "BattleFrontier_BattlePyramidSquare88", "BattleFrontier_BattlePyramidSquare89", "BattleFrontier_BattlePyramidSquare90",
    "BattleFrontier_BattlePyramidSquare91", "BattleFrontier_BattlePyramidSquare92", "BattleFrontier_BattlePyramidSquare93", "BattleFrontier_BattlePyramidSquare94",
    "BattleFrontier_BattlePyramidSquare95", "BattleFrontier_BattlePyramidSquare96", "BattleFrontier_BattlePyramidSquare97", "BattleFrontier_BattlePyramidSquare98",
    "BattleFrontier_BattlePyramidSquare99", "BattleFrontier_BattlePyramidTop", "BattleFrontier_BattlePyramid_WildMonRoom", "BattleFrontier_BattleTentBattleRoom",
    "BattleFrontier_BattleTentCorridor", "BattleFrontier_BattleTentLobby", "BattleFrontier_Northwest", "BattleFrontier_OutsideEast", "BattleFrontier_OutsideWest",
    "BattleFrontier_PokemonCenter_1F", "BattleFrontier_PokemonCenter_2F", "BattleFrontier_ScottQuarters", "BattleFrontier_Stadium", "BirthIsland_Exterior",
    "ContestHall", "ContestHall_Beauty", "ContestHall_Cool", "ContestHall_Cute", "ContestHall_Smart", "ContestHall_Tough", "DewfordTown",
    "DewfordTown_Gym", "DewfordTown_Hall", "DewfordTown_House1", "DewfordTown_House2", "DewfordTown_PokemonCenter_1F", "DewfordTown_PokemonCenter_2F",
    "DewfordTown_TownHall", "DewfordTown_WaterfallCave", "DesertRuins", "EverGrandeCity", "EverGrandeCity_ChampionsRoom", "EverGrandeCity_Hall1",
    "EverGrandeCity_Hall2", "EverGrandeCity_Hall3", "EverGrandeCity_Hall4", "EverGrandeCity_HallOfFame", "EverGrandeCity_PokemonLeague_1F", "EverGrandeCity_PokemonCenter_1F",
    "EverGrandeCity_PokemonCenter_2F", "FarawayIsland_Entrance", "FarawayIsland_Interior", "FallarborTown", "FallarborTown_BattleTentLobby", "FallarborTown_BattleTentCorridor",
    "FallarborTown_BattleTentBattleRoom", "FallarborTown_CozmosHouse", "FallarborTown_House1", "FallarborTown_Mart", "FallarborTown_MoveRelearnersHouse", "FallarborTown_PokemonCenter_1F",
    "FallarborTown_PokemonCenter_2F", "FallarborTown_PokemonContestLobby", "FieryPath", "FortreeCity", "FortreeCity_DecorationShop", "FortreeCity_Gym",
    "FortreeCity_House1", "FortreeCity_House2", "FortreeCity_House3", "FortreeCity_House4", "FortreeCity_House5", "FortreeCity_Mart", "FortreeCity_PokemonCenter_1F",
    "FortreeCity_PokemonCenter_2F", "GraniteCave_1F", "GraniteCave_B1F", "GraniteCave_B2F", "InsideOfTruck", "JaggedPass", "LavaridgeTown",
    "LavaridgeTown_Gym_1F", "LavaridgeTown_Gym_B1F", "LavaridgeTown_HerbShop", "LavaridgeTown_House", "LavaridgeTown_Mart", "LavaridgeTown_PokemonCenter_1F",
    "LavaridgeTown_PokemonCenter_2F", "LavaridgeTown_PokemonHerbShop", "LavaridgeTown_PokemonHouse", "LilycoveCity", "LilycoveCity_ContestLobby", "LilycoveCity_ContestHall",
    "LilycoveCity_CoveLilyMotel_1F", "LilycoveCity_CoveLilyMotel_2F", "LilycoveCity_DepartmentStore_1F", "LilycoveCity_DepartmentStore_2F", "LilycoveCity_DepartmentStore_3F",
    "LilycoveCity_DepartmentStore_4F", "LilycoveCity_DepartmentStore_5F", "LilycoveCity_DepartmentStore_Elevator", "LilycoveCity_DepartmentStore_Rooftop", "LilycoveCity_Harbor",
    "LilycoveCity_House1", "LilycoveCity_House2", "LilycoveCity_House3", "LilycoveCity_House4", "LilycoveCity_House5", "LilycoveCity_Mart", "LilycoveCity_Museum_1F",
    "LilycoveCity_Museum_2F", "LilycoveCity_PokemonCenter_1F", "LilycoveCity_PokemonCenter_2F", "LittlerootTown", "LittlerootTown_BrendansHouse_1F", "LittlerootTown_BrendansHouse_2F",
    "LittlerootTown_MaysHouse_1F", "LittlerootTown_MaysHouse_2F", "LittlerootTown_ProfessorBirchsLab", "MarineCave_End", "MarineCave_Entrance", "MarineCave_Underwater",
    "MauvilleCity", "MauvilleCity_BikeShop", "MauvilleCity_GameCorner", "MauvilleCity_Gym", "MauvilleCity_House1", "MauvilleCity_House2", "MauvilleCity_Mart",
    "MauvilleCity_PokemonCenter_1F", "MauvilleCity_PokemonCenter_2F", "MeteorFalls_1F_1R", "MeteorFalls_1F_2R", "MeteorFalls_B1F_1R", "MeteorFalls_B1F_2R",
    "MirageTower_1F", "MirageTower_2F", "MirageTower_3F", "MirageTower_4F", "MossdeepCity", "MossdeepCity_Gym", "MossdeepCity_House1", "MossdeepCity_House2",
    "MossdeepCity_Mart", "MossdeepCity_PokemonCenter_1F", "MossdeepCity_PokemonCenter_2F", "MossdeepCity_SpaceCenter_1F", "MossdeepCity_SpaceCenter_2F", "MtChimney",
    "NavelRock_Bottom", "NavelRock_Down01", "NavelRock_Down02", "NavelRock_Down03", "NavelRock_Down04", "NavelRock_Down05", "NavelRock_Down06", "NavelRock_Down07",
    "NavelRock_Down08", "NavelRock_Down09", "NavelRock_Down10", "NavelRock_Down11", "NavelRock_Exterior", "NavelRock_Fork", "NavelRock_Summit", "NavelRock_Top",
    "NavelRock_Up1", "NavelRock_Up2", "NavelRock_Up3", "NavelRock_Up4", "NavelRock_Up5", "NavelRock_Up6", "NavelRock_Up7", "NavelRock_Up8",
    "NavelRock_Up9", "OldaleTown", "OldaleTown_House1", "OldaleTown_House2", "OldaleTown_Mart", "OldaleTown_PokemonCenter_1F", "OldaleTown_PokemonCenter_2F",
    "PacifidlogTown", "PacifidlogTown_House1", "PacifidlogTown_House2", "PacifidlogTown_House3", "PacifidlogTown_House4", "PacifidlogTown_House5", "PacifidlogTown_PokemonCenter_1F",
    "PacifidlogTown_PokemonCenter_2F", "PetalburgCity", "PetalburgCity_Gym", "PetalburgCity_House1", "PetalburgCity_House2", "PetalburgCity_Mart", "PetalburgCity_PokemonCenter_1F",
    "PetalburgCity_PokemonCenter_2F", "PetalburgCity_WallysHouse", "PetalburgWoods", "RecordCorner", "Route101", "Route102", "Route103", "Route104", "Route104_MrBrineysHouse",
    "Route104_PrettyPetalFlowerShop", "Route104_Prototype", "Route104_PrototypePrettyPetalFlowerShop", "Route105", "Route106", "Route107", "Route108", "Route109",
    "Route109_SeashoreHouse", "Route110", "Route110_SeasideCyclingRoadNorthEntrance", "Route110_SeasideCyclingRoadSouthEntrance", "Route110_TrickHouseCorridor", "Route110_TrickHouseEnd",
    "Route110_TrickHouseEntrance", "Route110_TrickHousePuzzle1", "Route110_TrickHousePuzzle2", "Route110_TrickHousePuzzle3", "Route110_TrickHousePuzzle4", "Route110_TrickHousePuzzle5",
    "Route110_TrickHousePuzzle6", "Route110_TrickHousePuzzle7", "Route110_TrickHousePuzzle8", "Route111", "Route111_OldLadysRestStop", "Route111_WinstrateFamilysHouse", "Route112",
    "Route112_CableCarStation", "Route113", "Route113_GlassWorkshop", "Route114", "Route114_FossilManiacsHouse", "Route114_FossilManiacsTunnel", "Route114_LanettesHouse", "Route115",
    "Route116", "Route116_TunnelersRestHouse", "Route117", "Route117_PokemonDayCare", "Route118", "Route119", "Route119_House", "Route119_WeatherInstitute_1F",
    "Route119_WeatherInstitute_2F", "Route120", "Route121", "Route121_SafariZoneEntrance", "Route122", "Route123", "Route123_BerryMastersHouse", "Route124",
    "Route124_DivingTreasureHuntersHouse", "Route125", "Route126", "Route127", "Route128", "Route129", "Route130", "Route131", "Route132", "Route133",
    "Route134", "RustboroCity", "RustboroCity_CuttersHouse", "RustboroCity_Flat1_1F", "RustboroCity_Flat1_2F", "RustboroCity_Flat2_1F", "RustboroCity_Flat2_2F",
    "RustboroCity_DevonCorp_1F", "RustboroCity_DevonCorp_2F", "RustboroCity_DevonCorp_3F", "RustboroCity_Gym", "RustboroCity_House1", "RustboroCity_House2",
    "RustboroCity_House3", "RustboroCity_Mart", "RustboroCity_PokemonCenter_1F", "RustboroCity_PokemonCenter_2F", "RusturfTunnel", "SafariZone_North", "SafariZone_Northeast",
    "SafariZone_Northwest", "SafariZone_RestHouse", "SafariZone_South", "SafariZone_Southeast", "SafariZone_Southwest", "ScorchedSlab", "SeafloorCavern_Entrance", "SeafloorCavern_Room1",
    "SeafloorCavern_Room2", "SeafloorCavern_Room3", "SeafloorCavern_Room4", "SeafloorCavern_Room5", "SeafloorCavern_Room6", "SeafloorCavern_Room7", "SeafloorCavern_Room8",
    "SeafloorCavern_Room9", "ShoalCave_HighTideEntranceRoom", "ShoalCave_HighTideInnerRoom", "ShoalCave_LowTideEntranceRoom", "ShoalCave_LowTideIceRoom", "ShoalCave_LowTideInnerRoom",
    "ShoalCave_LowTideLowerRoom", "SlateportCity", "SlateportCity_BattleTentBattleRoom", "SlateportCity_BattleTentCorridor", "SlateportCity_BattleTentLobby", "SlateportCity_Harbor",
    "SlateportCity_House1", "SlateportCity_House2", "SlateportCity_Mart", "SlateportCity_OceanicMuseum_1F", "SlateportCity_OceanicMuseum_2F", "SlateportCity_PokemonCenter_1F",
    "SlateportCity_PokemonCenter_2F", "SlateportCity_PokemonFanClub", "SlateportCity_Shipyard_1F", "SlateportCity_Shipyard_2F", "SouthernIsland_Exterior", "SouthernIsland_Interior",
    "SootopolisCity", "SootopolisCity_Gym_1F", "SootopolisCity_Gym_B1F", "SootopolisCity_House1", "SootopolisCity_House2", "SootopolisCity_House3", "SootopolisCity_House4",
    "SootopolisCity_House5", "SootopolisCity_House6", "SootopolisCity_House7", "SootopolisCity_House8", "SootopolisCity_LotadAndSeedotHouse", "SootopolisCity_MysteryEventsHouse_1F",
    "SootopolisCity_MysteryEventsHouse_B1F", "SootopolisCity_PokemonCenter_1F", "SootopolisCity_PokemonCenter_2F", "SootopolisCity_PokemonContestLobby", "SootopolisCity_PokemonContestHall",
    "SootopolisCity_Mart", "SpecialArea_SecretBase_PC", "TerraCave_End", "TerraCave_Entrance", "TrainerHill_1F", "TrainerHill_2F", "TrainerHill_3F", "TrainerHill_4F",
    "TrainerHill_Elevator", "Underwater1", "Underwater2", "Underwater3", "Underwater4", "Underwater5", "Underwater6", "Underwater7", "Underwater_Route105",
    "Underwater_Route124", "Underwater_Route125", "Underwater_Route126", "Underwater_Route127", "Underwater_Route128", "Underwater_Route129", "Underwater_Route134", "UnionRoom",
    "VerdanturfTown", "VerdanturfTown_BattleTentBattleRoom", "VerdanturfTown_BattleTentCorridor", "VerdanturfTown_BattleTentLobby", "VerdanturfTown_FriendshipRatersHouse", "VerdanturfTown_House",
    "VerdanturfTown_Mart", "VerdanturfTown_PokemonCenter_1F", "VerdanturfTown_PokemonCenter_2F", "VictoryRoad_1F", "VictoryRoad_B1F", "VictoryRoad_B2F", "WonderNewsHouse_2F",
    "WonderNewsHouse_1F",
    # Additional names verified against the current upstream data/maps tree and newer expansion naming
    "AbandonedShip_Rooms2_B1F", "AbandonedShip_Rooms_B1F", "AlteringCave", "AncientTomb",
    "AquaHideout_1F", "AquaHideout_B1F", "AquaHideout_B2F",
    "AquaHideout_UnusedRubyMap1", "AquaHideout_UnusedRubyMap2", "AquaHideout_UnusedRubyMap3",
    "BattleColosseum_2P_Frlg", "BattleColosseum_4P_Frlg",
    "BattleFrontier_BattleArenaBattleRoom", "BattleFrontier_BattleArenaCorridor", "BattleFrontier_BattleArenaLobby",
    "BattleFrontier_BattleDomeBattleRoom", "BattleFrontier_BattleDomeCorridor", "BattleFrontier_BattleDomeLobby", "BattleFrontier_BattleDomePreBattleRoom",
    "BattleFrontier_BattleFactoryBattleRoom", "BattleFrontier_BattleFactoryLobby", "BattleFrontier_BattleFactoryPreBattleRoom",
    "BattleFrontier_BattlePalaceBattleRoom", "BattleFrontier_BattlePalaceCorridor", "BattleFrontier_BattlePalaceLobby",
    "BattleFrontier_BattlePikeRoomNormal", "BattleFrontier_BattlePikeRoomWildMons",
    "BattleFrontier_BattleTowerBattleRoom", "BattleFrontier_BattleTowerCorridor", "BattleFrontier_BattleTowerElevator",
    "BattleFrontier_BattleTowerMultiCorridor", "BattleFrontier_BattleTowerMultiPartnerRoom",
    "BattleFrontier_Lounge3", "BattleFrontier_Lounge4", "BattleFrontier_Lounge5", "BattleFrontier_Lounge6",
    "BattleFrontier_Lounge7", "BattleFrontier_Lounge8", "BattleFrontier_Lounge9",
    "BattleFrontier_ScottsHouse",
    "BattlePyramidSquare01", "BattlePyramidSquare02", "BattlePyramidSquare03", "BattlePyramidSquare04", "BattlePyramidSquare05",
    "BattlePyramidSquare06", "BattlePyramidSquare07", "BattlePyramidSquare08", "BattlePyramidSquare09", "BattlePyramidSquare10",
    "BattlePyramidSquare11", "BattlePyramidSquare12", "BattlePyramidSquare13", "BattlePyramidSquare14", "BattlePyramidSquare15",
    "BattlePyramidSquare16",
    "BirthIsland_Exterior_Frlg", "BirthIsland_Harbor", "BirthIsland_Harbor_Frlg",
    "CaveOfOrigin_1F", "CaveOfOrigin_B1F", "CaveOfOrigin_Entrance",
    "CaveOfOrigin_UnusedRubySapphireMap1", "CaveOfOrigin_UnusedRubySapphireMap2", "CaveOfOrigin_UnusedRubySapphireMap3",
}

VANILLA_NAME_PATTERNS = [
    re.compile(r"^BattlePyramidSquare\d+$"),
    re.compile(r"^BattleFrontier_Lounge\d+$"),
    re.compile(r"^BattleColosseum_[24]P_Frlg$"),
    re.compile(r"^BirthIsland_(Exterior|Harbor)_Frlg$"),
    re.compile(r"^AquaHideout_UnusedRubyMap\d+$"),
    re.compile(r"^CaveOfOrigin_UnusedRubySapphireMap\d+$"),
]


def is_probably_vanilla_map_name(name: str) -> bool:
    if name in CANONICAL_VANILLA_MAPS:
        return True
    return any(pattern.match(name) for pattern in VANILLA_NAME_PATTERNS)


@dataclass
class TeamMon:
    name: str = ""
    growth_rate: str = "Medium Slow"
    start_level: int = 5
    level_progress_pct: float = 0.0
    traded: bool = False
    lucky_egg: bool = False
    unevolved_bonus: bool = False


@dataclass
class EnemyMon:
    species: str = ""
    level: int = 5
    base_exp: int = 60
    is_trainer_mon: bool = True
    suggested_level: int | None = None


@dataclass
class TrainerEntry:
    name: str = "Trainer"
    trainer_class: str = "Youngster"
    notes: str = ""
    enemy_mons: list[EnemyMon] = field(default_factory=list)
    source_trainer_id: str = ""
    source_script: str = ""


@dataclass
class RouteEntry:
    name: str = "Neue Route"
    avg_active_battlers: float = 1.0
    participation_rates: list[float] = field(default_factory=lambda: [100.0, 0.0, 0.0, 0.0, 0.0, 0.0])
    trainers: list[TrainerEntry] = field(default_factory=list)
    notes: str = ""
    enabled: bool = True
    is_vanilla: bool = False
    imported: bool = False
    source_map: str = ""
    source_map_type: str = ""
    source_map_path: str = ""
    uid: str = ""


@dataclass
class PlannerSettings:
    preset_name: str = "pokeemerald-expansion modern"
    use_scaled_exp: bool = True
    trainer_multiplier: float = 1.0
    use_exp_share_for_bench: bool = True
    bench_exp_factor: float = 0.5
    use_unevolved_bonus: bool = True
    traded_bonus: float = 1.5
    lucky_egg_bonus: float = 1.5
    suggestion_offset: float = 0.0
    suggestion_spread: float = 1.0
    ace_offset: float = 2.0


@dataclass
class ProjectData:
    team: list[TeamMon] = field(default_factory=list)
    routes: list[RouteEntry] = field(default_factory=list)
    route_plan: list[str] = field(default_factory=list)
    settings: PlannerSettings = field(default_factory=PlannerSettings)
    species_db: dict[str, dict[str, Any]] = field(default_factory=dict)
    repo_root: str = ""


@dataclass
class ParsedTrainerParty:
    trainer_id: str
    name: str
    trainer_class: str
    mons: list[dict[str, Any]]


# -----------------------------
# Utility
# -----------------------------

def clamp(value: float, low: float, high: float) -> float:
    return max(low, min(high, value))


def round_half_down(value: float) -> int:
    frac = value - math.floor(value)
    if abs(frac - 0.5) < 1e-9:
        return math.floor(value)
    return int(round(value))


def normalize_key(text: str) -> str:
    return re.sub(r"[^a-z0-9]", "", text.lower())


def title_from_species_constant(species_constant: str) -> str:
    raw = species_constant.removeprefix("SPECIES_")
    parts = raw.split("_")
    return " ".join(p.capitalize() for p in parts if p)


def growth_rate_from_constant(value: str) -> str:
    value = value.strip().upper()
    mapping = {
        "GROWTH_ERRATIC": "Erratic",
        "GROWTH_FAST": "Fast",
        "GROWTH_MEDIUM_FAST": "Medium Fast",
        "GROWTH_MEDIUM_SLOW": "Medium Slow",
        "GROWTH_SLOW": "Slow",
        "GROWTH_FLUCTUATING": "Fluctuating",
    }
    return mapping.get(value, "Medium Fast")


def growth_rate_to_constant(label: str) -> str:
    mapping = {
        "Erratic": "GROWTH_ERRATIC",
        "Fast": "GROWTH_FAST",
        "Medium Fast": "GROWTH_MEDIUM_FAST",
        "Medium Slow": "GROWTH_MEDIUM_SLOW",
        "Slow": "GROWTH_SLOW",
        "Fluctuating": "GROWTH_FLUCTUATING",
    }
    return mapping.get(label, "GROWTH_MEDIUM_FAST")


def dataclass_from_dict(cls, data: dict[str, Any]):
    kwargs: dict[str, Any] = {}
    for f in fields(cls):
        if f.name not in data:
            continue
        value = data[f.name]
        if cls is TrainerEntry and f.name == "enemy_mons":
            kwargs[f.name] = [EnemyMon(**x) if not isinstance(x, EnemyMon) else x for x in value]
        elif cls is RouteEntry and f.name == "trainers":
            kwargs[f.name] = [
                dataclass_from_dict(TrainerEntry, x) if not isinstance(x, TrainerEntry) else x for x in value
            ]
        else:
            kwargs[f.name] = value
    return cls(**kwargs)


def safe_asdict(obj: Any) -> Any:
    if is_dataclass(obj):
        return {k: safe_asdict(v) for k, v in asdict(obj).items()}
    if isinstance(obj, list):
        return [safe_asdict(x) for x in obj]
    if isinstance(obj, dict):
        return {k: safe_asdict(v) for k, v in obj.items()}
    return obj


# -----------------------------
# Growth / Exp
# -----------------------------

class Growth:
    @staticmethod
    def exp_for_level(growth_rate: str, level: int) -> int:
        n = int(clamp(level, 1, 100))
        if n <= 1:
            return 0
        if growth_rate == "Fast":
            return (4 * n ** 3) // 5
        if growth_rate == "Medium Fast":
            return n ** 3
        if growth_rate == "Medium Slow":
            return max(0, (6 * n ** 3) // 5 - 15 * n ** 2 + 100 * n - 140)
        if growth_rate == "Slow":
            return (5 * n ** 3) // 4
        if growth_rate == "Erratic":
            if n <= 50:
                return n ** 3 * (100 - n) // 50
            if n <= 68:
                return n ** 3 * (150 - n) // 100
            if n <= 98:
                return n ** 3 * (1911 - 10 * n) // 1500
            return n ** 3 * (160 - n) // 100
        if growth_rate == "Fluctuating":
            if n <= 15:
                return n ** 3 * (((n + 1) // 3) + 24) // 50
            if n <= 36:
                return n ** 3 * (n + 14) // 50
            return n ** 3 * ((n // 2) + 32) // 50
        return n ** 3

    @staticmethod
    def level_from_exp(growth_rate: str, exp: float) -> int:
        exp_int = max(0, int(exp))
        level = 1
        for n in range(1, 101):
            if Growth.exp_for_level(growth_rate, n) <= exp_int:
                level = n
            else:
                break
        return level

    @staticmethod
    def start_exp_from_level_and_progress(growth_rate: str, level: int, progress_pct: float) -> float:
        base = Growth.exp_for_level(growth_rate, level)
        if level >= 100:
            return float(base)
        nxt = Growth.exp_for_level(growth_rate, level + 1)
        return base + (nxt - base) * clamp(progress_pct, 0.0, 100.0) / 100.0

    @staticmethod
    def progress_pct_from_exp(growth_rate: str, exp: float) -> float:
        level = Growth.level_from_exp(growth_rate, exp)
        if level >= 100:
            return 100.0
        low = Growth.exp_for_level(growth_rate, level)
        high = Growth.exp_for_level(growth_rate, level + 1)
        span = max(1, high - low)
        return clamp((exp - low) * 100.0 / span, 0.0, 100.0)


class ExpEngine:
    @staticmethod
    def gain_flat(enemy: EnemyMon, mon_level: int, settings: PlannerSettings, s_value: float) -> int:
        a = settings.trainer_multiplier if enemy.is_trainer_mon else 1.0
        base = math.floor(enemy.base_exp * enemy.level / 7.0)
        result = base * a * (1.0 / max(1e-9, s_value))
        return max(1, math.floor(result))

    @staticmethod
    def gain_scaled(enemy: EnemyMon, mon_level: int, settings: PlannerSettings, s_value: float) -> int:
        a = settings.trainer_multiplier if enemy.is_trainer_mon else 1.0
        base = math.floor((enemy.base_exp * enemy.level) / 5.0)
        scale_num = (2 * enemy.level + 10) ** 2.5
        scale_den = (enemy.level + mon_level + 10) ** 2.5
        scale = scale_num / scale_den if scale_den else 1.0
        result = (base * a * (1.0 / max(1e-9, s_value)) * scale) + 1.0
        return max(1, math.floor(result))

    @staticmethod
    def apply_mon_multipliers(base_exp: int, mon: TeamMon, settings: PlannerSettings) -> int:
        value = float(base_exp)
        if mon.traded:
            value *= settings.traded_bonus
        if mon.lucky_egg:
            value *= settings.lucky_egg_bonus
        if settings.use_unevolved_bonus and mon.unevolved_bonus:
            value *= 4915 / 4096
        return max(1, round_half_down(value))

    @staticmethod
    def expected_gain_for_mon(
        enemy: EnemyMon,
        mon: TeamMon,
        current_level: int,
        participation_rate: float,
        avg_active_battlers: float,
        settings: PlannerSettings,
    ) -> float:
        p = clamp(participation_rate / 100.0, 0.0, 1.0)
        if settings.use_scaled_exp:
            direct = ExpEngine.gain_scaled(enemy, current_level, settings, 1.0)
            bench = ExpEngine.gain_scaled(enemy, current_level, settings, 2.0) if settings.use_exp_share_for_bench else 0
            if settings.use_exp_share_for_bench:
                bench = math.floor(bench * settings.bench_exp_factor / 0.5)
        else:
            direct = ExpEngine.gain_flat(enemy, current_level, settings, max(1.0, avg_active_battlers))
            bench = ExpEngine.gain_flat(enemy, current_level, settings, 2.0) if settings.use_exp_share_for_bench else 0
            if settings.use_exp_share_for_bench:
                bench = math.floor(bench * settings.bench_exp_factor / 0.5)
        expected_base = (direct * p) + (bench * (1.0 - p))
        return float(ExpEngine.apply_mon_multipliers(int(expected_base), mon, settings))


# -----------------------------
# Repo parser
# -----------------------------

class RepoParser:
    SCRIPT_EXTENSIONS = {".inc", ".pory", ".s", ".txt"}

    def __init__(self, repo_root: Path):
        self.repo_root = repo_root
        self.species_db: dict[str, dict[str, Any]] = {}
        self.trainer_parties: dict[str, ParsedTrainerParty] = {}
        self.script_to_trainer: dict[str, str] = {}

    def parse(self) -> tuple[list[RouteEntry], dict[str, dict[str, Any]]]:
        self.species_db = self.parse_species_db()
        self.trainer_parties = self.parse_trainer_parties()
        self.script_to_trainer = self.parse_script_index()
        routes = self.parse_maps()
        return routes, self.species_db

    def parse_species_db(self) -> dict[str, dict[str, Any]]:
        db: dict[str, dict[str, Any]] = {}
        species_root = self.repo_root / "src" / "data" / "pokemon" / "species_info"
        candidates: list[Path] = []
        if species_root.exists():
            candidates.extend(sorted(species_root.rglob("*.h")))
        root_file = self.repo_root / "src" / "data" / "pokemon" / "species_info.h"
        if root_file.exists():
            candidates.append(root_file)

        for path in candidates:
            try:
                text = path.read_text(encoding="utf-8", errors="ignore")
            except OSError:
                continue
            for constant, block in self._iter_species_blocks(text):
                entry = self._species_entry_from_block(constant, block)
                if entry is None:
                    continue
                key = normalize_key(entry["display_name"])
                db[key] = entry
                db[normalize_key(constant)] = entry
        return db

    def _iter_species_blocks(self, text: str) -> Iterable[tuple[str, str]]:
        lines = text.splitlines()
        current_constant: str | None = None
        pending_constant: str | None = None
        current_lines: list[str] = []
        depth = 0
        block_decl_re = re.compile(r"\[\s*(SPECIES_[A-Z0-9_]+)\s*\]\s*=")
        for line in lines:
            if current_constant is None:
                if pending_constant is None:
                    m = block_decl_re.search(line)
                    if not m:
                        continue
                    pending_constant = m.group(1)
                    current_lines = [line]
                    if "{" not in line:
                        continue
                else:
                    current_lines.append(line)
                if "{" in line:
                    current_constant = pending_constant
                    pending_constant = None
                    depth = 0
                    for existing in current_lines:
                        depth += existing.count("{") - existing.count("}")
                    if depth <= 0 and current_constant is not None:
                        yield current_constant, "\n".join(current_lines)
                        current_constant = None
                        current_lines = []
                        depth = 0
            else:
                current_lines.append(line)
                depth += line.count("{") - line.count("}")
                if depth <= 0:
                    yield current_constant, "\n".join(current_lines)
                    current_constant = None
                    current_lines = []
                    depth = 0

    def _species_entry_from_block(self, constant: str, block: str) -> dict[str, Any] | None:
        display_name = title_from_species_constant(constant)
        name_match = re.search(r'\.speciesName\s*=\s*_\("([^"]+)"\)', block)
        if name_match:
            display_name = name_match.group(1).strip()
        exp_match = re.search(r"\.expYield\s*=\s*([^,\n]+)", block)
        growth_match = re.search(r"\.growthRate\s*=\s*([A-Z0-9_]+)", block)
        if not exp_match and not growth_match:
            return None
        base_exp = self._parse_exp_yield_expression(exp_match.group(1)) if exp_match else 1
        growth_rate = growth_rate_from_constant(growth_match.group(1)) if growth_match else "Medium Fast"
        return {
            "display_name": display_name,
            "base_exp": int(max(1, base_exp)),
            "growth_rate": growth_rate,
            "species_constant": constant,
        }

    def _parse_exp_yield_expression(self, expr: str) -> int:
        expr = expr.strip()
        if "?" in expr:
            tail = expr.split("?", 1)[1]
            m = re.search(r"(\d+)", tail)
            if m:
                return int(m.group(1))
        nums = re.findall(r"\d+", expr)
        if nums:
            return int(nums[-1])
        return 1

    def parse_trainer_parties(self) -> dict[str, ParsedTrainerParty]:
        path = self.repo_root / "src" / "data" / "trainers.party"
        parties: dict[str, ParsedTrainerParty] = {}
        if not path.exists():
            return parties
        text = path.read_text(encoding="utf-8", errors="ignore")
        matches = list(re.finditer(r"(?m)^===\s*(TRAINER_[A-Z0-9_]+)\s*===\s*$", text))
        for idx, match in enumerate(matches):
            trainer_id = match.group(1)
            start = match.end()
            end = matches[idx + 1].start() if idx + 1 < len(matches) else len(text)
            section = text[start:end].strip()
            parsed = self._parse_trainer_section(trainer_id, section)
            if parsed:
                parties[trainer_id] = parsed
        return parties

    def _parse_trainer_section(self, trainer_id: str, section: str) -> ParsedTrainerParty | None:
        lines = [line.rstrip() for line in section.splitlines()]
        header: dict[str, str] = {}
        mon_blocks: list[list[str]] = []
        current: list[str] = []
        in_mons = False
        for line in lines:
            stripped = line.strip()
            if not stripped:
                if in_mons and current:
                    mon_blocks.append(current)
                    current = []
                elif header:
                    in_mons = True
                continue
            if not in_mons and ":" in stripped:
                k, v = stripped.split(":", 1)
                header[k.strip()] = v.strip()
                continue
            in_mons = True
            current.append(stripped)
        if current:
            mon_blocks.append(current)
        mons = []
        for block in mon_blocks:
            mon = self._parse_showdown_mon(block)
            if mon:
                mons.append(mon)
        return ParsedTrainerParty(
            trainer_id=trainer_id,
            name=header.get("Name", trainer_id.removeprefix("TRAINER_")),
            trainer_class=header.get("Class", "PkMn Trainer"),
            mons=mons,
        )

    def _parse_showdown_mon(self, lines: list[str]) -> dict[str, Any] | None:
        if not lines:
            return None
        species_line = lines[0]
        species = self._parse_species_name_from_showdown_header(species_line)
        level = 100
        for line in lines[1:]:
            if line.startswith("Level:"):
                m = re.search(r"(\d+)", line)
                if m:
                    level = int(m.group(1))
                    break
        key = normalize_key(species)
        entry = self.species_db.get(key)
        base_exp = int(entry["base_exp"]) if entry else 60
        display_name = entry["display_name"] if entry else species
        return {"species": display_name, "level": level, "base_exp": base_exp}

    def _parse_species_name_from_showdown_header(self, header: str) -> str:
        if header.startswith("SPECIES_"):
            token = header.split("@", 1)[0].strip().split()[0]
            return title_from_species_constant(token)
        m = re.search(r"\((SPECIES_[A-Z0-9_]+|[^()]+)\)", header)
        if m and m.group(1) not in {"M", "F"}:
            inside = m.group(1).strip()
            if inside.startswith("SPECIES_"):
                return title_from_species_constant(inside)
            return inside
        clean = header.split("@", 1)[0].strip()
        clean = re.sub(r"\s*\((M|F)\)$", "", clean).strip()
        return clean.split("(", 1)[0].strip()

    def parse_script_index(self) -> dict[str, str]:
        script_map: dict[str, str] = {}
        candidates: list[Path] = []
        for base in [self.repo_root / "data" / "maps", self.repo_root / "data" / "scripts", self.repo_root / "data"]:
            if base.exists():
                for path in base.rglob("*"):
                    if path.is_file() and path.suffix in self.SCRIPT_EXTENSIONS and path.name != "map.json":
                        candidates.append(path)
        for path in sorted(set(candidates)):
            try:
                text = path.read_text(encoding="utf-8", errors="ignore")
            except OSError:
                continue
            script_map.update(self._parse_inc_style_script_blocks(text))
            script_map.update(self._parse_pory_style_script_blocks(text))
        return script_map

    def _parse_inc_style_script_blocks(self, text: str) -> dict[str, str]:
        result: dict[str, str] = {}
        pattern = re.compile(r"(?ms)^\s*([A-Za-z0-9_]+)\s*::?\s*(.*?)(?=^\s*[A-Za-z0-9_]+\s*::?|\Z)")
        for label, block in pattern.findall(text):
            trainer = self._extract_trainer_id_from_script_block(block)
            if trainer:
                result[label] = trainer
        return result

    def _parse_pory_style_script_blocks(self, text: str) -> dict[str, str]:
        result: dict[str, str] = {}
        pattern = re.compile(r"(?ms)^\s*(?:script|mapscript)\s+([A-Za-z0-9_]+)\s*\{(.*?)^\s*\}")
        for label, block in pattern.findall(text):
            trainer = self._extract_trainer_id_from_script_block(block)
            if trainer:
                result[label] = trainer
        return result

    def _extract_trainer_id_from_script_block(self, block: str) -> str | None:
        if "TRAINER_" not in block:
            return None
        m = re.search(r"\bTRAINER_[A-Z0-9_]+\b", block)
        return m.group(0) if m else None

    def parse_maps(self) -> list[RouteEntry]:
        maps_root = self.repo_root / "data" / "maps"
        routes: list[RouteEntry] = []
        if not maps_root.exists():
            return routes
        for path in sorted(maps_root.rglob("map.json")):
            route = self._parse_single_map(path)
            if route is not None:
                routes.append(route)
        return routes

    def _parse_single_map(self, path: Path) -> RouteEntry | None:
        try:
            data = json.loads(path.read_text(encoding="utf-8"))
        except Exception:
            return None
        map_name = str(data.get("name") or path.parent.name)
        map_type = str(data.get("map_type") or "")
        trainers: list[TrainerEntry] = []
        for event in data.get("object_events", []):
            script_name = str(event.get("script") or "").strip()
            trainer_type = str(event.get("trainer_type") or "TRAINER_TYPE_NONE")
            if not script_name or script_name == "0x0":
                continue
            trainer_id = self.script_to_trainer.get(script_name)
            if trainer_id is None and trainer_type == "TRAINER_TYPE_NONE":
                continue
            entry = self._build_trainer_entry(script_name, trainer_id, event)
            if entry:
                trainers.append(entry)
        if not trainers:
            return None
        is_vanilla = is_probably_vanilla_map_name(path.parent.name) or is_probably_vanilla_map_name(map_name)
        route = RouteEntry(
            name=map_name,
            trainers=trainers,
            enabled=not is_vanilla,
            is_vanilla=is_vanilla,
            imported=True,
            source_map=map_name,
            source_map_type=map_type,
            source_map_path=str(path),
        )
        return route

    def _build_trainer_entry(self, script_name: str, trainer_id: str | None, event: dict[str, Any]) -> TrainerEntry | None:
        if trainer_id and trainer_id in self.trainer_parties:
            party = self.trainer_parties[trainer_id]
            enemy_mons = [EnemyMon(species=m["species"], level=int(m["level"]), base_exp=int(m["base_exp"]), is_trainer_mon=True) for m in party.mons]
            notes = []
            if str(event.get("trainer_sight_or_berry_tree_id", "0")) not in {"0", ""}:
                notes.append(f"Sichtweite: {event.get('trainer_sight_or_berry_tree_id')}")
            return TrainerEntry(
                name=party.name,
                trainer_class=party.trainer_class,
                notes=" | ".join(notes),
                enemy_mons=enemy_mons,
                source_trainer_id=trainer_id,
                source_script=script_name,
            )
        if trainer_id:
            return TrainerEntry(
                name=trainer_id.removeprefix("TRAINER_"),
                trainer_class="Unbekannt",
                notes=f"Trainerdaten für {trainer_id} nicht in trainers.party gefunden.",
                enemy_mons=[EnemyMon(species="Unbekannt", level=1, base_exp=60, is_trainer_mon=True)],
                source_trainer_id=trainer_id,
                source_script=script_name,
            )
        return None


# -----------------------------
# Dialoge
# -----------------------------

class TeamMonDialog(simpledialog.Dialog):
    def __init__(self, parent: tk.Misc, species_db: dict[str, dict[str, Any]], title: str, mon: TeamMon | None = None):
        self.species_db = species_db
        self.mon = mon or TeamMon()
        self.result_data: TeamMon | None = None
        super().__init__(parent, title)

    def body(self, master: tk.Misc):
        ttk.Label(master, text="Name / Spezies:").grid(row=0, column=0, sticky="w", padx=6, pady=4)
        self.name_var = tk.StringVar(value=self.mon.name)
        species_values = sorted({entry.get("display_name", key) for key, entry in self.species_db.items() if entry.get("display_name")})
        self.name_box = ttk.Combobox(master, textvariable=self.name_var, values=species_values)
        self.name_box.grid(row=0, column=1, sticky="ew", padx=6, pady=4)
        self.name_box.bind("<<ComboboxSelected>>", self._auto_fill_from_species)

        ttk.Label(master, text="Wachstumsrate:").grid(row=1, column=0, sticky="w", padx=6, pady=4)
        self.growth_var = tk.StringVar(value=self.mon.growth_rate)
        ttk.Combobox(master, textvariable=self.growth_var, values=GROWTH_RATES, state="readonly").grid(row=1, column=1, sticky="ew", padx=6, pady=4)

        ttk.Label(master, text="Startlevel:").grid(row=2, column=0, sticky="w", padx=6, pady=4)
        self.level_var = tk.StringVar(value=str(self.mon.start_level))
        ttk.Entry(master, textvariable=self.level_var).grid(row=2, column=1, sticky="ew", padx=6, pady=4)

        ttk.Label(master, text="Fortschritt zum nächsten Level (%):").grid(row=3, column=0, sticky="w", padx=6, pady=4)
        self.progress_var = tk.StringVar(value=str(self.mon.level_progress_pct))
        ttk.Entry(master, textvariable=self.progress_var).grid(row=3, column=1, sticky="ew", padx=6, pady=4)

        self.traded_var = tk.BooleanVar(value=self.mon.traded)
        self.lucky_var = tk.BooleanVar(value=self.mon.lucky_egg)
        self.unevolved_var = tk.BooleanVar(value=self.mon.unevolved_bonus)
        ttk.Checkbutton(master, text="Getauscht / Outsider", variable=self.traded_var).grid(row=4, column=0, columnspan=2, sticky="w", padx=6, pady=2)
        ttk.Checkbutton(master, text="Lucky Egg", variable=self.lucky_var).grid(row=5, column=0, columnspan=2, sticky="w", padx=6, pady=2)
        ttk.Checkbutton(master, text="Nicht entwickelt trotz möglicher Entwicklung (1.2x)", variable=self.unevolved_var).grid(row=6, column=0, columnspan=2, sticky="w", padx=6, pady=2)
        master.columnconfigure(1, weight=1)
        return self.name_box

    def _auto_fill_from_species(self, _event=None):
        key = normalize_key(self.name_var.get().strip())
        entry = self.species_db.get(key)
        if entry and entry.get("growth_rate") in GROWTH_RATES:
            self.growth_var.set(entry["growth_rate"])

    def validate(self) -> bool:
        try:
            level = int(self.level_var.get())
            progress = float(self.progress_var.get())
            if not (1 <= level <= 100 and 0.0 <= progress <= 100.0):
                raise ValueError
        except ValueError:
            messagebox.showerror("Ungültige Eingabe", "Bitte gültiges Level (1-100) und Fortschritt (0-100) eingeben.")
            return False
        if not self.name_var.get().strip():
            messagebox.showerror("Fehlende Eingabe", "Bitte einen Namen oder eine Spezies eingeben.")
            return False
        return True

    def apply(self):
        self.result_data = TeamMon(
            name=self.name_var.get().strip(),
            growth_rate=self.growth_var.get().strip() or "Medium Slow",
            start_level=int(self.level_var.get()),
            level_progress_pct=float(self.progress_var.get()),
            traded=self.traded_var.get(),
            lucky_egg=self.lucky_var.get(),
            unevolved_bonus=self.unevolved_var.get(),
        )


class EnemyMonDialog(simpledialog.Dialog):
    def __init__(self, parent: tk.Misc, species_db: dict[str, dict[str, Any]], title: str, mon: EnemyMon | None = None):
        self.species_db = species_db
        self.mon = mon or EnemyMon()
        self.result_data: EnemyMon | None = None
        super().__init__(parent, title)

    def body(self, master: tk.Misc):
        ttk.Label(master, text="Spezies / Label:").grid(row=0, column=0, sticky="w", padx=6, pady=4)
        self.species_var = tk.StringVar(value=self.mon.species)
        species_values = sorted({entry.get("display_name", key) for key, entry in self.species_db.items() if entry.get("display_name")})
        self.species_box = ttk.Combobox(master, textvariable=self.species_var, values=species_values)
        self.species_box.grid(row=0, column=1, sticky="ew", padx=6, pady=4)
        self.species_box.bind("<<ComboboxSelected>>", self._auto_fill_from_species)

        ttk.Label(master, text="Level:").grid(row=1, column=0, sticky="w", padx=6, pady=4)
        self.level_var = tk.StringVar(value=str(self.mon.level))
        ttk.Entry(master, textvariable=self.level_var).grid(row=1, column=1, sticky="ew", padx=6, pady=4)

        ttk.Label(master, text="Base EXP Yield:").grid(row=2, column=0, sticky="w", padx=6, pady=4)
        self.base_exp_var = tk.StringVar(value=str(self.mon.base_exp))
        ttk.Entry(master, textvariable=self.base_exp_var).grid(row=2, column=1, sticky="ew", padx=6, pady=4)

        master.columnconfigure(1, weight=1)
        return self.species_box

    def _auto_fill_from_species(self, _event=None):
        key = normalize_key(self.species_var.get().strip())
        entry = self.species_db.get(key)
        if entry and entry.get("base_exp") is not None:
            self.base_exp_var.set(str(entry["base_exp"]))

    def validate(self) -> bool:
        try:
            level = int(self.level_var.get())
            base_exp = int(self.base_exp_var.get())
            if not (1 <= level <= 100 and base_exp > 0):
                raise ValueError
        except ValueError:
            messagebox.showerror("Ungültige Eingabe", "Bitte gültiges Level (1-100) und Base EXP (>0) eingeben.")
            return False
        if not self.species_var.get().strip():
            messagebox.showerror("Fehlende Eingabe", "Bitte eine Spezies oder ein Label eingeben.")
            return False
        return True

    def apply(self):
        self.result_data = EnemyMon(
            species=self.species_var.get().strip(),
            level=int(self.level_var.get()),
            base_exp=int(self.base_exp_var.get()),
            is_trainer_mon=True,
        )


class TrainerDialog(simpledialog.Dialog):
    def __init__(self, parent: tk.Misc, species_db: dict[str, dict[str, Any]], title: str, trainer: TrainerEntry | None = None):
        self.species_db = species_db
        self.trainer = trainer or TrainerEntry(enemy_mons=[EnemyMon()])
        self.result_data: TrainerEntry | None = None
        self.enemy_mons = [EnemyMon(**safe_asdict(m)) for m in self.trainer.enemy_mons]
        super().__init__(parent, title)

    def body(self, master: tk.Misc):
        ttk.Label(master, text="Trainername:").grid(row=0, column=0, sticky="w", padx=6, pady=4)
        self.name_var = tk.StringVar(value=self.trainer.name)
        ttk.Entry(master, textvariable=self.name_var).grid(row=0, column=1, sticky="ew", padx=6, pady=4)

        ttk.Label(master, text="Trainerklasse:").grid(row=1, column=0, sticky="w", padx=6, pady=4)
        self.class_var = tk.StringVar(value=self.trainer.trainer_class)
        ttk.Entry(master, textvariable=self.class_var).grid(row=1, column=1, sticky="ew", padx=6, pady=4)

        ttk.Label(master, text="Notizen:").grid(row=2, column=0, sticky="nw", padx=6, pady=4)
        self.notes_text = tk.Text(master, width=42, height=3)
        self.notes_text.grid(row=2, column=1, sticky="ew", padx=6, pady=4)
        self.notes_text.insert("1.0", self.trainer.notes)

        ttk.Label(master, text="Pokémon des Trainers:").grid(row=3, column=0, columnspan=2, sticky="w", padx=6, pady=(8, 4))
        self.tree = ttk.Treeview(master, columns=("species", "level", "exp"), show="headings", height=7)
        for col, label, width in (("species", "Spezies", 170), ("level", "Lv", 60), ("exp", "Base EXP", 90)):
            self.tree.heading(col, text=label)
            self.tree.column(col, width=width, anchor="center" if col != "species" else "w")
        self.tree.grid(row=4, column=0, columnspan=2, sticky="nsew", padx=6, pady=4)

        btn_frame = ttk.Frame(master)
        btn_frame.grid(row=5, column=0, columnspan=2, sticky="ew", padx=6, pady=4)
        ttk.Button(btn_frame, text="Hinzufügen", command=self.add_mon).pack(side="left", padx=2)
        ttk.Button(btn_frame, text="Bearbeiten", command=self.edit_mon).pack(side="left", padx=2)
        ttk.Button(btn_frame, text="Löschen", command=self.delete_mon).pack(side="left", padx=2)

        master.columnconfigure(1, weight=1)
        master.rowconfigure(4, weight=1)
        self.refresh_tree()
        return None

    def refresh_tree(self):
        for item in self.tree.get_children():
            self.tree.delete(item)
        for idx, mon in enumerate(self.enemy_mons):
            self.tree.insert("", "end", iid=str(idx), values=(mon.species, mon.level, mon.base_exp))

    def add_mon(self):
        dlg = EnemyMonDialog(self, self.species_db, "Trainer-Pokémon hinzufügen")
        if dlg.result_data:
            self.enemy_mons.append(dlg.result_data)
            self.refresh_tree()

    def edit_mon(self):
        selection = self.tree.selection()
        if not selection:
            return
        idx = int(selection[0])
        dlg = EnemyMonDialog(self, self.species_db, "Trainer-Pokémon bearbeiten", self.enemy_mons[idx])
        if dlg.result_data:
            self.enemy_mons[idx] = dlg.result_data
            self.refresh_tree()

    def delete_mon(self):
        selection = self.tree.selection()
        if not selection:
            return
        idx = int(selection[0])
        del self.enemy_mons[idx]
        self.refresh_tree()

    def validate(self) -> bool:
        if not self.name_var.get().strip() or not self.class_var.get().strip() or not self.enemy_mons:
            messagebox.showerror("Fehlende Eingabe", "Bitte Namen, Klasse und mindestens ein Pokémon angeben.")
            return False
        return True

    def apply(self):
        self.result_data = TrainerEntry(
            name=self.name_var.get().strip(),
            trainer_class=self.class_var.get().strip(),
            notes=self.notes_text.get("1.0", "end").strip(),
            enemy_mons=self.enemy_mons,
            source_trainer_id=self.trainer.source_trainer_id,
            source_script=self.trainer.source_script,
        )


class RouteDialog(simpledialog.Dialog):
    def __init__(self, parent: tk.Misc, species_db: dict[str, dict[str, Any]], title: str, route: RouteEntry | None = None):
        self.species_db = species_db
        self.route = route or RouteEntry()
        self.result_data: RouteEntry | None = None
        self.trainers = [dataclass_from_dict(TrainerEntry, safe_asdict(t)) for t in self.route.trainers]
        super().__init__(parent, title)

    def body(self, master: tk.Misc):
        ttk.Label(master, text="Routenname:").grid(row=0, column=0, sticky="w", padx=6, pady=4)
        self.name_var = tk.StringVar(value=self.route.name)
        ttk.Entry(master, textvariable=self.name_var).grid(row=0, column=1, sticky="ew", padx=6, pady=4)

        ttk.Label(master, text="Ø aktive Team-Pokémon pro besiegtem Gegner:").grid(row=1, column=0, sticky="w", padx=6, pady=4)
        self.active_var = tk.StringVar(value=str(self.route.avg_active_battlers))
        ttk.Entry(master, textvariable=self.active_var).grid(row=1, column=1, sticky="ew", padx=6, pady=4)

        part_frame = ttk.LabelFrame(master, text="Beteiligung pro Team-Slot auf dieser Route (%)")
        part_frame.grid(row=2, column=0, columnspan=2, sticky="ew", padx=6, pady=6)
        self.part_vars: list[tk.StringVar] = []
        for idx in range(MAX_TEAM_SIZE):
            ttk.Label(part_frame, text=f"Slot {idx + 1}:").grid(row=idx // 3, column=(idx % 3) * 2, sticky="w", padx=6, pady=4)
            value = self.route.participation_rates[idx] if idx < len(self.route.participation_rates) else 0.0
            var = tk.StringVar(value=str(value))
            self.part_vars.append(var)
            ttk.Entry(part_frame, textvariable=var, width=8).grid(row=idx // 3, column=(idx % 3) * 2 + 1, sticky="w", padx=4, pady=4)

        ttk.Label(master, text="Trainer auf der Route:").grid(row=3, column=0, columnspan=2, sticky="w", padx=6, pady=(8, 4))
        self.tree = ttk.Treeview(master, columns=("name", "class", "mons"), show="headings", height=8)
        for col, label, width in (("name", "Name", 190), ("class", "Klasse", 150), ("mons", "Pokémon", 80)):
            self.tree.heading(col, text=label)
            self.tree.column(col, width=width, anchor="center" if col == "mons" else "w")
        self.tree.grid(row=4, column=0, columnspan=2, sticky="nsew", padx=6, pady=4)

        btn_frame = ttk.Frame(master)
        btn_frame.grid(row=5, column=0, columnspan=2, sticky="ew", padx=6, pady=4)
        ttk.Button(btn_frame, text="Trainer hinzufügen", command=self.add_trainer).pack(side="left", padx=2)
        ttk.Button(btn_frame, text="Bearbeiten", command=self.edit_trainer).pack(side="left", padx=2)
        ttk.Button(btn_frame, text="Löschen", command=self.delete_trainer).pack(side="left", padx=2)

        self.enabled_var = tk.BooleanVar(value=self.route.enabled)
        ttk.Checkbutton(master, text="Route in Berechnung aktiv", variable=self.enabled_var).grid(row=6, column=0, columnspan=2, sticky="w", padx=6, pady=4)

        ttk.Label(master, text="Notizen:").grid(row=7, column=0, sticky="nw", padx=6, pady=4)
        self.notes_text = tk.Text(master, width=50, height=4)
        self.notes_text.grid(row=7, column=1, sticky="ew", padx=6, pady=4)
        self.notes_text.insert("1.0", self.route.notes)

        master.columnconfigure(1, weight=1)
        master.rowconfigure(4, weight=1)
        self.refresh_tree()
        return None

    def refresh_tree(self):
        for item in self.tree.get_children():
            self.tree.delete(item)
        for idx, trainer in enumerate(self.trainers):
            self.tree.insert("", "end", iid=str(idx), values=(trainer.name, trainer.trainer_class, len(trainer.enemy_mons)))

    def add_trainer(self):
        dlg = TrainerDialog(self, self.species_db, "Trainer hinzufügen")
        if dlg.result_data:
            self.trainers.append(dlg.result_data)
            self.refresh_tree()

    def edit_trainer(self):
        selection = self.tree.selection()
        if not selection:
            return
        idx = int(selection[0])
        dlg = TrainerDialog(self, self.species_db, "Trainer bearbeiten", self.trainers[idx])
        if dlg.result_data:
            self.trainers[idx] = dlg.result_data
            self.refresh_tree()

    def delete_trainer(self):
        selection = self.tree.selection()
        if not selection:
            return
        idx = int(selection[0])
        del self.trainers[idx]
        self.refresh_tree()

    def validate(self) -> bool:
        try:
            active = float(self.active_var.get())
            if not (0.1 <= active <= 6.0):
                raise ValueError
            for var in self.part_vars:
                if not (0.0 <= float(var.get()) <= 100.0):
                    raise ValueError
        except ValueError:
            messagebox.showerror("Ungültige Eingabe", "Bitte gültige Zahlen für aktive Pokémon und Beteiligung eingeben.")
            return False
        if not self.name_var.get().strip():
            messagebox.showerror("Fehlende Eingabe", "Bitte einen Routennamen eingeben.")
            return False
        return True

    def apply(self):
        self.result_data = RouteEntry(
            name=self.name_var.get().strip(),
            avg_active_battlers=float(self.active_var.get()),
            participation_rates=[float(v.get()) for v in self.part_vars],
            trainers=self.trainers,
            notes=self.notes_text.get("1.0", "end").strip(),
            enabled=self.enabled_var.get(),
            is_vanilla=self.route.is_vanilla,
            imported=self.route.imported,
            source_map=self.route.source_map,
            source_map_type=self.route.source_map_type,
            source_map_path=self.route.source_map_path,
        )


# -----------------------------
# Application
# -----------------------------


class PlannerApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title(APP_TITLE)
        self.geometry("1560x920")
        self.minsize(1260, 780)
        self.project = ProjectData()
        self.current_project_path: Path | None = None
        self._last_csv_rows: list[list[str]] | None = None
        self._last_analysis_by_route_name: dict[str, dict[str, Any]] = {}
        self.detail_route_uid: str | None = None
        self._drag_plan_uid: str | None = None
        self._build_menu()
        self._build_ui()
        self.apply_preset(self.project.settings.preset_name, from_user=False)
        self.migrate_project_state()
        self.refresh_all()

    def _build_menu(self):
        menu = tk.Menu(self)
        file_menu = tk.Menu(menu, tearoff=False)
        file_menu.add_command(label="Neues Projekt", command=self.new_project)
        file_menu.add_command(label="Projekt laden…", command=self.load_project)
        file_menu.add_command(label="Projekt speichern", command=self.save_project)
        file_menu.add_command(label="Projekt speichern unter…", command=self.save_project_as)
        file_menu.add_separator()
        file_menu.add_command(label="Expansion-Projekt importieren…", command=self.import_repo_project)
        file_menu.add_command(label="Spezies-CSV laden…", command=self.load_species_csv)
        file_menu.add_command(label="Routen-Zusammenfassung als CSV exportieren…", command=self.export_results_csv)
        file_menu.add_separator()
        file_menu.add_command(label="Beenden", command=self.destroy)
        menu.add_cascade(label="Datei", menu=file_menu)

        help_menu = tk.Menu(menu, tearoff=False)
        help_menu.add_command(label="Annahmen / Hilfe", command=self.show_help)
        menu.add_cascade(label="Hilfe", menu=help_menu)
        self.config(menu=menu)

    def _build_ui(self):
        top = ttk.Frame(self)
        top.pack(fill="both", expand=True)

        header = ttk.Frame(top, padding=10)
        header.pack(fill="x")
        ttk.Label(header, text=APP_TITLE, font=("TkDefaultFont", 15, "bold")).pack(side="left")
        ttk.Button(header, text="Berechnungsliste berechnen", command=self.calculate).pack(side="right", padx=4)
        ttk.Button(header, text="Expansion importieren", command=self.import_repo_project).pack(side="right", padx=4)
        ttk.Button(header, text="Spezies-CSV laden", command=self.load_species_csv).pack(side="right", padx=4)

        self.notebook = ttk.Notebook(top)
        self.notebook.pack(fill="both", expand=True, padx=10, pady=(0, 10))

        self.team_tab = ttk.Frame(self.notebook, padding=10)
        self.routes_tab = ttk.Frame(self.notebook, padding=10)
        self.settings_tab = ttk.Frame(self.notebook, padding=10)
        self.results_tab = ttk.Frame(self.notebook, padding=10)
        self.notebook.add(self.team_tab, text="Team")
        self.notebook.add(self.routes_tab, text="Routenplanung")
        self.notebook.add(self.settings_tab, text="Einstellungen")
        self.notebook.add(self.results_tab, text="Ergebnisse")

        self._build_team_tab()
        self._build_routes_tab()
        self._build_settings_tab()
        self._build_results_tab()

    def _build_team_tab(self):
        ttk.Label(
            self.team_tab,
            text="Hier legst du dein Spielerteam fest. Growth Rate ist wichtig, weil sie bestimmt, wie schnell das Team levelt.",
            foreground="#444444",
        ).pack(fill="x", pady=(0, 8))

        self.team_tree = ttk.Treeview(
            self.team_tab,
            columns=("name", "growth", "level", "progress", "traded", "egg", "unevolved"),
            show="headings",
            height=12,
        )
        for col, label, width, anchor in [
            ("name", "Name / Spezies", 220, "w"),
            ("growth", "Growth", 120, "w"),
            ("level", "Start-Lv", 70, "center"),
            ("progress", "%", 70, "center"),
            ("traded", "Getauscht", 90, "center"),
            ("egg", "Lucky Egg", 90, "center"),
            ("unevolved", "1.2x Evo", 90, "center"),
        ]:
            self.team_tree.heading(col, text=label)
            self.team_tree.column(col, width=width, anchor=anchor)
        self.team_tree.pack(fill="both", expand=True)

        btns = ttk.Frame(self.team_tab)
        btns.pack(fill="x", pady=8)
        ttk.Button(btns, text="Pokémon hinzufügen", command=self.add_team_mon).pack(side="left", padx=3)
        ttk.Button(btns, text="Bearbeiten", command=self.edit_team_mon).pack(side="left", padx=3)
        ttk.Button(btns, text="Löschen", command=self.delete_team_mon).pack(side="left", padx=3)
        ttk.Button(btns, text="Nach oben", command=lambda: self.move_team_mon(-1)).pack(side="left", padx=3)
        ttk.Button(btns, text="Nach unten", command=lambda: self.move_team_mon(1)).pack(side="left", padx=3)

    def _build_routes_tab(self):
        top_info = ttk.Frame(self.routes_tab)
        top_info.pack(fill="x", pady=(0, 8))
        ttk.Label(
            top_info,
            text="Links sind alle importierten oder manuell angelegten Maps. Doppelklick fügt eine Route in die Berechnungsliste ein. "
                 "Rechts ziehst du Einträge per Drag-and-drop in die gewünschte Spielreihenfolge und klickst dann auf Berechnen.",
            foreground="#444444",
            wraplength=1460,
        ).pack(anchor="w")

        top_pane = ttk.Panedwindow(self.routes_tab, orient="horizontal")
        top_pane.pack(fill="both", expand=True)
        left = ttk.Frame(top_pane)
        mid = ttk.Frame(top_pane, padding=(6, 40, 6, 0))
        right = ttk.Frame(top_pane)
        top_pane.add(left, weight=1)
        top_pane.add(mid, weight=0)
        top_pane.add(right, weight=1)

        filter_frame = ttk.LabelFrame(left, text="Alle importierten Maps")
        filter_frame.pack(fill="both", expand=True)
        filter_controls = ttk.Frame(filter_frame)
        filter_controls.pack(fill="x", padx=6, pady=6)
        self.hide_vanilla_var = tk.BooleanVar(value=False)
        self.hide_planned_var = tk.BooleanVar(value=False)
        ttk.Checkbutton(filter_controls, text="Vanilla ausblenden", variable=self.hide_vanilla_var, command=self.refresh_route_trees).pack(anchor="w")
        ttk.Checkbutton(filter_controls, text="Bereits in Liste verstecken", variable=self.hide_planned_var, command=self.refresh_route_trees).pack(anchor="w")
        self.repo_label_var = tk.StringVar(value="Kein Repo importiert")
        ttk.Label(filter_controls, textvariable=self.repo_label_var, foreground="#555555", wraplength=330).pack(anchor="w", pady=(4, 2))

        self.available_route_tree = ttk.Treeview(
            filter_frame,
            columns=("planned", "vanilla", "maptype", "trainers", "mons"),
            show="tree headings",
            height=22,
        )
        self.available_route_tree.heading("#0", text="Route / Map")
        self.available_route_tree.column("#0", width=270, anchor="w")
        self.available_route_tree.heading("planned", text="In Liste")
        self.available_route_tree.column("planned", width=65, anchor="center")
        self.available_route_tree.heading("vanilla", text="Vanilla")
        self.available_route_tree.column("vanilla", width=60, anchor="center")
        self.available_route_tree.heading("maptype", text="Map-Typ")
        self.available_route_tree.column("maptype", width=115, anchor="w")
        self.available_route_tree.heading("trainers", text="Trainer")
        self.available_route_tree.column("trainers", width=60, anchor="center")
        self.available_route_tree.heading("mons", text="Pokémon")
        self.available_route_tree.column("mons", width=70, anchor="center")
        self.available_route_tree.pack(fill="both", expand=True, padx=6, pady=(0, 6))
        self.available_route_tree.bind("<<TreeviewSelect>>", self.on_available_route_select)
        self.available_route_tree.bind("<Double-1>", self.on_available_route_double_click)

        left_btns = ttk.Frame(filter_frame)
        left_btns.pack(fill="x", padx=6, pady=(0, 6))
        ttk.Button(left_btns, text="Aus Repo importieren", command=self.import_repo_project).pack(fill="x", pady=2)
        ttk.Button(left_btns, text="Manuelle Route hinzufügen", command=self.add_route).pack(fill="x", pady=2)
        ttk.Button(left_btns, text="Bearbeiten", command=self.edit_route).pack(fill="x", pady=2)
        ttk.Button(left_btns, text="Als Vanilla / Custom umschalten", command=self.toggle_route_vanilla).pack(fill="x", pady=2)
        ttk.Button(left_btns, text="Alle Vanilla aus Liste entfernen", command=self.remove_all_vanilla_from_plan).pack(fill="x", pady=2)
        ttk.Button(left_btns, text="Route komplett löschen", command=self.delete_route).pack(fill="x", pady=2)

        ttk.Button(mid, text="→\nIn Liste", command=self.add_selected_available_to_plan).pack(fill="x", pady=4)
        ttk.Button(mid, text="←\nRaus", command=self.remove_selected_plan_route).pack(fill="x", pady=4)
        ttk.Separator(mid, orient="horizontal").pack(fill="x", pady=8)
        ttk.Button(mid, text="Berechnen", command=self.calculate).pack(fill="x", pady=4)

        plan_frame = ttk.LabelFrame(right, text="Berechnungsliste / Spielreihenfolge")
        plan_frame.pack(fill="both", expand=True)
        ttk.Label(
            plan_frame,
            text="Nur die Einträge in dieser Liste werden berechnet. Drag-and-drop oder Nach oben/Nach unten ändert die Reihenfolge.",
            foreground="#555555",
            wraplength=360,
        ).pack(anchor="w", padx=6, pady=(6, 4))

        self.plan_tree = ttk.Treeview(
            plan_frame,
            columns=("pos", "maptype", "trainers", "mons"),
            show="tree headings",
            height=18,
        )
        self.plan_tree.heading("#0", text="Route / Map")
        self.plan_tree.column("#0", width=285, anchor="w")
        self.plan_tree.heading("pos", text="#")
        self.plan_tree.column("pos", width=45, anchor="center")
        self.plan_tree.heading("maptype", text="Map-Typ")
        self.plan_tree.column("maptype", width=110, anchor="w")
        self.plan_tree.heading("trainers", text="Trainer")
        self.plan_tree.column("trainers", width=60, anchor="center")
        self.plan_tree.heading("mons", text="Pokémon")
        self.plan_tree.column("mons", width=70, anchor="center")
        self.plan_tree.pack(fill="both", expand=True, padx=6, pady=(0, 6))
        self.plan_tree.bind("<<TreeviewSelect>>", self.on_plan_route_select)
        self.plan_tree.bind("<ButtonPress-1>", self.on_plan_press)
        self.plan_tree.bind("<ButtonRelease-1>", self.on_plan_release)

        plan_btns = ttk.Frame(plan_frame)
        plan_btns.pack(fill="x", padx=6, pady=(0, 6))
        ttk.Button(plan_btns, text="Nach oben", command=lambda: self.move_selected_plan_route(-1)).pack(side="left", padx=3)
        ttk.Button(plan_btns, text="Nach unten", command=lambda: self.move_selected_plan_route(1)).pack(side="left", padx=3)
        ttk.Button(plan_btns, text="Aus Liste entfernen", command=self.remove_selected_plan_route).pack(side="left", padx=3)
        ttk.Button(plan_btns, text="Leeren", command=self.clear_plan).pack(side="right", padx=3)

        detail_frame = ttk.LabelFrame(right, text="Details & berechnete Anpassungen")
        detail_frame.pack(fill="both", expand=True, padx=0, pady=(6, 0))
        self.route_detail_text = tk.Text(detail_frame, wrap="word")
        self.route_detail_text.pack(fill="both", expand=True, padx=6, pady=6)

    def _build_settings_tab(self):
        frm = ttk.Frame(self.settings_tab)
        frm.pack(anchor="nw", fill="x")
        frm.columnconfigure(1, weight=1)
        row = 0

        ttk.Label(frm, text="Preset:").grid(row=row, column=0, sticky="w", padx=6, pady=4)
        self.preset_var = tk.StringVar(value=self.project.settings.preset_name)
        preset_box = ttk.Combobox(frm, textvariable=self.preset_var, values=PRESETS, state="readonly")
        preset_box.grid(row=row, column=1, sticky="ew", padx=6, pady=4)
        preset_box.bind("<<ComboboxSelected>>", lambda _e: self.apply_preset(self.preset_var.get(), from_user=True))
        row += 1

        self.scaled_var = tk.BooleanVar(value=True)
        ttk.Checkbutton(frm, text="Scaled EXP verwenden", variable=self.scaled_var).grid(row=row, column=0, columnspan=2, sticky="w", padx=6, pady=2)
        row += 1
        ttk.Label(frm, text="Trainer-Multiplikator:").grid(row=row, column=0, sticky="w", padx=6, pady=4)
        self.trainer_mult_var = tk.StringVar(value="1.0")
        ttk.Entry(frm, textvariable=self.trainer_mult_var).grid(row=row, column=1, sticky="ew", padx=6, pady=4)
        row += 1

        self.exp_share_var = tk.BooleanVar(value=True)
        ttk.Checkbutton(frm, text="Bench-EXP / modernes Teilen berücksichtigen", variable=self.exp_share_var).grid(row=row, column=0, columnspan=2, sticky="w", padx=6, pady=2)
        row += 1
        ttk.Label(frm, text="Bench-EXP-Faktor:").grid(row=row, column=0, sticky="w", padx=6, pady=4)
        self.bench_factor_var = tk.StringVar(value="0.5")
        ttk.Entry(frm, textvariable=self.bench_factor_var).grid(row=row, column=1, sticky="ew", padx=6, pady=4)
        row += 1

        self.unevolved_bonus_var = tk.BooleanVar(value=True)
        ttk.Checkbutton(frm, text="Unevolved Bonus erlauben", variable=self.unevolved_bonus_var).grid(row=row, column=0, columnspan=2, sticky="w", padx=6, pady=2)
        row += 1

        ttk.Label(frm, text="Tauschbonus:").grid(row=row, column=0, sticky="w", padx=6, pady=4)
        self.traded_bonus_var = tk.StringVar(value="1.5")
        ttk.Entry(frm, textvariable=self.traded_bonus_var).grid(row=row, column=1, sticky="ew", padx=6, pady=4)
        row += 1
        ttk.Label(frm, text="Lucky-Egg-Bonus:").grid(row=row, column=0, sticky="w", padx=6, pady=4)
        self.lucky_bonus_var = tk.StringVar(value="1.5")
        ttk.Entry(frm, textvariable=self.lucky_bonus_var).grid(row=row, column=1, sticky="ew", padx=6, pady=4)
        row += 1

        ttk.Separator(frm).grid(row=row, column=0, columnspan=2, sticky="ew", padx=6, pady=10)
        row += 1
        ttk.Label(frm, text="Vorschlag: Offset zum Team-Ø nach Route:").grid(row=row, column=0, sticky="w", padx=6, pady=4)
        self.suggestion_offset_var = tk.StringVar(value="0.0")
        ttk.Entry(frm, textvariable=self.suggestion_offset_var).grid(row=row, column=1, sticky="ew", padx=6, pady=4)
        row += 1
        ttk.Label(frm, text="Vorschlag: Standardtrainer-Spanne:").grid(row=row, column=0, sticky="w", padx=6, pady=4)
        self.suggestion_spread_var = tk.StringVar(value="1.0")
        ttk.Entry(frm, textvariable=self.suggestion_spread_var).grid(row=row, column=1, sticky="ew", padx=6, pady=4)
        row += 1
        ttk.Label(frm, text="Vorschlag: Ace/Boss-Offset:").grid(row=row, column=0, sticky="w", padx=6, pady=4)
        self.ace_offset_var = tk.StringVar(value="2.0")
        ttk.Entry(frm, textvariable=self.ace_offset_var).grid(row=row, column=1, sticky="ew", padx=6, pady=4)

    def _build_results_tab(self):
        top_frame = ttk.Frame(self.results_tab)
        top_frame.pack(fill="x")
        ttk.Label(top_frame, text="Berechnete Levelkurve", font=("TkDefaultFont", 11, "bold")).pack(side="left")
        ttk.Button(top_frame, text="Vorschläge auf gewählte Route anwenden", command=self.apply_suggestions_to_selected_route).pack(side="right")

        self.result_tree = ttk.Treeview(
            self.results_tab,
            columns=("route", "before", "after", "gain", "enemy_avg", "next_avg", "range", "ace"),
            show="headings",
            height=14,
        )
        cols = [
            ("route", "Route", 220, "w"),
            ("before", "Team-Ø davor", 110, "center"),
            ("after", "Team-Ø danach", 110, "center"),
            ("gain", "Ø Gewinn", 100, "center"),
            ("enemy_avg", "Gegner-Ø jetzt", 110, "center"),
            ("next_avg", "Soll-Ø nächstes Gebiet", 150, "center"),
            ("range", "Standardtrainer", 140, "center"),
            ("ace", "Ace/Boss", 100, "center"),
        ]
        for col, label, width, anchor in cols:
            self.result_tree.heading(col, text=label)
            self.result_tree.column(col, width=width, anchor=anchor)
        self.result_tree.pack(fill="x")
        self.result_tree.bind("<<TreeviewSelect>>", self.on_result_select)

        lower = ttk.Panedwindow(self.results_tab, orient="horizontal")
        lower.pack(fill="both", expand=True, pady=(10, 0))
        left = ttk.Frame(lower)
        right = ttk.Frame(lower)
        lower.add(left, weight=1)
        lower.add(right, weight=1)

        ttk.Label(left, text="Finale Teamwerte", font=("TkDefaultFont", 11, "bold")).pack(anchor="w")
        self.final_team_tree = ttk.Treeview(left, columns=("name", "level", "progress", "exp"), show="headings", height=12)
        for col, label, width in (("name", "Pokémon", 180), ("level", "Level", 70), ("progress", "% zum nächsten", 120), ("exp", "Gesamt-EXP", 120)):
            self.final_team_tree.heading(col, text=label)
            self.final_team_tree.column(col, width=width, anchor="center" if col != "name" else "w")
        self.final_team_tree.pack(fill="both", expand=True)

        ttk.Label(right, text="Routenanalyse / Änderungshilfe", font=("TkDefaultFont", 11, "bold")).pack(anchor="w")
        self.result_notes = tk.Text(right, wrap="word")
        self.result_notes.pack(fill="both", expand=True)
        self.result_notes.configure(state="disabled")

    # ---------- helpers ----------
    def migrate_project_state(self):
        seen: set[str] = set()
        for route in self.project.routes:
            if not route.uid or route.uid in seen:
                route.uid = uuid4().hex
            seen.add(route.uid)
        if not getattr(self.project, "route_plan", None):
            self.project.route_plan = [route.uid for route in self.project.routes if route.enabled]
        self._sanitize_route_plan()
        if self.detail_route_uid and self._route_by_uid(self.detail_route_uid) is None:
            self.detail_route_uid = self.project.route_plan[0] if self.project.route_plan else (self.project.routes[0].uid if self.project.routes else None)

    def _sanitize_route_plan(self):
        valid_ids = {route.uid for route in self.project.routes}
        clean: list[str] = []
        seen: set[str] = set()
        for uid in self.project.route_plan:
            if uid in valid_ids and uid not in seen:
                clean.append(uid)
                seen.add(uid)
        self.project.route_plan = clean

    def _route_by_uid(self, uid: str | None) -> RouteEntry | None:
        if uid is None:
            return None
        for route in self.project.routes:
            if route.uid == uid:
                return route
        return None

    def _route_index_by_uid(self, uid: str | None) -> int | None:
        if uid is None:
            return None
        for idx, route in enumerate(self.project.routes):
            if route.uid == uid:
                return idx
        return None

    def _plan_routes(self) -> list[RouteEntry]:
        return [route for uid in self.project.route_plan if (route := self._route_by_uid(uid)) is not None]

    def _selected_available_uid(self) -> str | None:
        selection = self.available_route_tree.selection()
        return selection[0] if selection else None

    def _selected_plan_uid(self) -> str | None:
        selection = self.plan_tree.selection()
        return selection[0] if selection else None

    def _selected_or_detail_uid(self) -> str | None:
        return self._selected_plan_uid() or self._selected_available_uid() or self.detail_route_uid

    def _visible_route_uids(self) -> list[str]:
        planned = set(self.project.route_plan)
        uids: list[str] = []
        for route in self.project.routes:
            if self.hide_vanilla_var.get() and route.is_vanilla:
                continue
            if self.hide_planned_var.get() and route.uid in planned:
                continue
            uids.append(route.uid)
        return uids

    def _set_detail_route(self, uid: str | None):
        self.detail_route_uid = uid
        self.refresh_route_details()

    def _sync_tree_selection(self):
        uid = self.detail_route_uid
        if uid and self.available_route_tree.exists(uid):
            self.available_route_tree.selection_set(uid)
            self.available_route_tree.see(uid)
        else:
            self.available_route_tree.selection_remove(self.available_route_tree.selection())
        if uid and self.plan_tree.exists(uid):
            self.plan_tree.selection_set(uid)
            self.plan_tree.see(uid)
        else:
            self.plan_tree.selection_remove(self.plan_tree.selection())

    # ---------- refresh ----------
    def refresh_all(self):
        self.migrate_project_state()
        self.refresh_team_tree()
        self.refresh_route_trees()
        self.refresh_route_details()
        self.refresh_settings_form()
        self.repo_label_var.set(self.project.repo_root or "Kein Repo importiert")

    def refresh_team_tree(self):
        for item in self.team_tree.get_children():
            self.team_tree.delete(item)
        for idx, mon in enumerate(self.project.team):
            self.team_tree.insert("", "end", iid=str(idx), values=(
                mon.name,
                mon.growth_rate,
                mon.start_level,
                f"{mon.level_progress_pct:.1f}",
                "Ja" if mon.traded else "Nein",
                "Ja" if mon.lucky_egg else "Nein",
                "Ja" if mon.unevolved_bonus else "Nein",
            ))

    def refresh_route_trees(self):
        self.migrate_project_state()
        selected_uid = self.detail_route_uid
        planned = set(self.project.route_plan)

        for widget in (self.available_route_tree, self.plan_tree):
            for item in widget.get_children():
                widget.delete(item)

        for uid in self._visible_route_uids():
            route = self._route_by_uid(uid)
            if route is None:
                continue
            self.available_route_tree.insert(
                "",
                "end",
                iid=uid,
                text=route.name,
                values=(
                    "Ja" if uid in planned else "Nein",
                    "Ja" if route.is_vanilla else "Nein",
                    route.source_map_type.replace("MAP_TYPE_", ""),
                    len(route.trainers),
                    sum(len(t.enemy_mons) for t in route.trainers),
                ),
            )

        for pos, uid in enumerate(self.project.route_plan, start=1):
            route = self._route_by_uid(uid)
            if route is None:
                continue
            self.plan_tree.insert(
                "",
                "end",
                iid=uid,
                text=route.name,
                values=(
                    pos,
                    route.source_map_type.replace("MAP_TYPE_", ""),
                    len(route.trainers),
                    sum(len(t.enemy_mons) for t in route.trainers),
                ),
            )

        if selected_uid is None:
            if self.project.route_plan:
                selected_uid = self.project.route_plan[0]
            elif self.project.routes:
                selected_uid = self.project.routes[0].uid
        self.detail_route_uid = selected_uid
        self._sync_tree_selection()

    def refresh_route_details(self):
        self.route_detail_text.configure(state="normal")
        self.route_detail_text.delete("1.0", "end")
        route = self._route_by_uid(self.detail_route_uid)
        if route is None:
            self.route_detail_text.insert(
                "1.0",
                "Wähle links eine Route aus oder füge sie per Doppelklick in die Berechnungsliste ein. "
                "Nach einer Berechnung siehst du hier die Vorschläge pro Trainer.",
            )
            self.route_detail_text.configure(state="disabled")
            return

        analysis = self._last_analysis_by_route_name.get(route.uid, {})
        suggestions_by_key = analysis.get("trainer_suggestions", {})
        try:
            plan_pos = self.project.route_plan.index(route.uid) + 1
            plan_text = f"Ja, Position {plan_pos}"
        except ValueError:
            plan_text = "Nein"

        lines = [
            f"Route / Map: {route.name}",
            f"In Berechnungsliste: {plan_text}",
            f"Vanilla-Basismap: {'Ja' if route.is_vanilla else 'Nein'}",
            f"Importiert: {'Ja' if route.imported else 'Nein'}",
            f"Map-Typ: {route.source_map_type or '-'}",
            f"Quelle: {route.source_map_path or '-'}",
            f"Ø aktive Team-Pokémon pro Gegner: {route.avg_active_battlers:.2f}",
            "",
            "Beteiligung pro Slot:",
        ]
        for slot, rate in enumerate(route.participation_rates, start=1):
            team_name = self.project.team[slot - 1].name if slot - 1 < len(self.project.team) else "(leer)"
            lines.append(f"  Slot {slot}: {rate:.1f}% -> {team_name}")

        lines.append("")
        lines.append("Trainer der Route:")
        for trainer_index, trainer in enumerate(route.trainers):
            key = f"{trainer.name}#{trainer_index}"
            lines.append(f"  - {trainer.trainer_class} {trainer.name} ({len(trainer.enemy_mons)} Pokémon)")
            if trainer.source_trainer_id:
                lines.append(f"      ID: {trainer.source_trainer_id} | Script: {trainer.source_script}")
            suggested_levels = suggestions_by_key.get(key, [])
            for mon_index, mon in enumerate(trainer.enemy_mons):
                suggestion_text = ""
                if mon_index < len(suggested_levels):
                    diff = int(suggested_levels[mon_index]) - int(mon.level)
                    sign = "+" if diff >= 0 else ""
                    suggestion_text = f" -> Vorschlag Lv{suggested_levels[mon_index]} ({sign}{diff})"
                battle_label = "Trainer" if mon.is_trainer_mon else "Wild"
                lines.append(f"      * {mon.species} Lv{mon.level}{suggestion_text} | Base EXP {mon.base_exp} | {battle_label}")
            if trainer.notes:
                lines.append(f"      Notiz: {trainer.notes}")

        if route.notes:
            lines.append("")
            lines.append(f"Routennotiz: {route.notes}")

        if analysis:
            lines.extend([
                "",
                f"Routen-Ø Gegnerlevel jetzt: {analysis.get('enemy_avg', 0):.2f}",
                f"Berechneter Team-Ø vor der Route: {analysis.get('before', 0):.2f}",
                f"Berechneter Team-Ø nach der Route: {analysis.get('after', 0):.2f}",
                f"Berechneter Ziel-Ø fürs nächste Gebiet: {analysis.get('target_avg', 0):.2f}",
                f"Standardtrainer-Vorschlag: {analysis.get('range', '-')}",
                f"Ace/Boss-Vorschlag: Lv{analysis.get('ace', '-')}",
            ])
        else:
            lines.extend([
                "",
                "Für diese Route liegt noch keine Berechnung vor.",
                "Füge die Route rechts in die Berechnungsliste ein und klicke dann auf Berechnen.",
            ])

        self.route_detail_text.insert("1.0", "\n".join(lines))
        self.route_detail_text.configure(state="disabled")

    def refresh_settings_form(self):
        s = self.project.settings
        self.preset_var.set(s.preset_name)
        self.scaled_var.set(s.use_scaled_exp)
        self.trainer_mult_var.set(str(s.trainer_multiplier))
        self.exp_share_var.set(s.use_exp_share_for_bench)
        self.bench_factor_var.set(str(s.bench_exp_factor))
        self.unevolved_bonus_var.set(s.use_unevolved_bonus)
        self.traded_bonus_var.set(str(s.traded_bonus))
        self.lucky_bonus_var.set(str(s.lucky_egg_bonus))
        self.suggestion_offset_var.set(str(s.suggestion_offset))
        self.suggestion_spread_var.set(str(s.suggestion_spread))
        self.ace_offset_var.set(str(s.ace_offset))

    def current_species_db(self) -> dict[str, dict[str, Any]]:
        return self.project.species_db

    # ---------- selection ----------
    def on_available_route_select(self, _event=None):
        uid = self._selected_available_uid()
        if uid:
            self._set_detail_route(uid)

    def on_plan_route_select(self, _event=None):
        uid = self._selected_plan_uid()
        if uid:
            self._set_detail_route(uid)

    def on_available_route_double_click(self, _event=None):
        self.add_selected_available_to_plan()

    def on_plan_press(self, event):
        self._drag_plan_uid = self.plan_tree.identify_row(event.y) or None

    def on_plan_release(self, event):
        if not self._drag_plan_uid:
            return
        target_uid = self.plan_tree.identify_row(event.y) or None
        source_uid = self._drag_plan_uid
        self._drag_plan_uid = None
        if target_uid is None or source_uid == target_uid:
            return
        if source_uid not in self.project.route_plan or target_uid not in self.project.route_plan:
            return
        source_idx = self.project.route_plan.index(source_uid)
        target_idx = self.project.route_plan.index(target_uid)
        uid = self.project.route_plan.pop(source_idx)
        self.project.route_plan.insert(target_idx, uid)
        self.refresh_route_trees()
        self._set_detail_route(uid)
        self.clear_results(keep_analysis=False)

    # ---------- team ----------
    def add_team_mon(self):
        if len(self.project.team) >= MAX_TEAM_SIZE:
            messagebox.showinfo("Team voll", f"Es sind maximal {MAX_TEAM_SIZE} Team-Pokémon möglich.")
            return
        dlg = TeamMonDialog(self, self.current_species_db(), "Team-Pokémon hinzufügen")
        if dlg.result_data:
            self.project.team.append(dlg.result_data)
            self.refresh_team_tree()
            self.refresh_route_details()

    def edit_team_mon(self):
        selection = self.team_tree.selection()
        if not selection:
            return
        idx = int(selection[0])
        dlg = TeamMonDialog(self, self.current_species_db(), "Team-Pokémon bearbeiten", self.project.team[idx])
        if dlg.result_data:
            self.project.team[idx] = dlg.result_data
            self.refresh_team_tree()
            self.refresh_route_details()

    def delete_team_mon(self):
        selection = self.team_tree.selection()
        if not selection:
            return
        idx = int(selection[0])
        del self.project.team[idx]
        self.refresh_team_tree()
        self.refresh_route_details()

    def move_team_mon(self, delta: int):
        selection = self.team_tree.selection()
        if not selection:
            return
        idx = int(selection[0])
        new_idx = idx + delta
        if not (0 <= new_idx < len(self.project.team)):
            return
        self.project.team[idx], self.project.team[new_idx] = self.project.team[new_idx], self.project.team[idx]
        self.refresh_team_tree()
        self.team_tree.selection_set(str(new_idx))
        self.refresh_route_details()

    # ---------- routes ----------
    def add_route(self):
        dlg = RouteDialog(self, self.current_species_db(), "Route hinzufügen")
        if dlg.result_data:
            if not dlg.result_data.uid:
                dlg.result_data.uid = uuid4().hex
            self.project.routes.append(dlg.result_data)
            self.refresh_route_trees()
            self._set_detail_route(dlg.result_data.uid)
            self.clear_results(keep_analysis=False)

    def edit_route(self):
        uid = self._selected_or_detail_uid()
        idx = self._route_index_by_uid(uid)
        if idx is None:
            return
        dlg = RouteDialog(self, self.current_species_db(), "Route bearbeiten", self.project.routes[idx])
        if dlg.result_data:
            dlg.result_data.uid = self.project.routes[idx].uid or uuid4().hex
            self.project.routes[idx] = dlg.result_data
            self.refresh_route_trees()
            self._set_detail_route(dlg.result_data.uid)
            self.clear_results(keep_analysis=False)

    def toggle_route_vanilla(self):
        uid = self._selected_or_detail_uid()
        route = self._route_by_uid(uid)
        if route is None:
            return
        route.is_vanilla = not route.is_vanilla
        self.refresh_route_trees()
        self.refresh_route_details()

    def delete_route(self):
        uid = self._selected_or_detail_uid()
        idx = self._route_index_by_uid(uid)
        if idx is None:
            return
        del self.project.routes[idx]
        self.project.route_plan = [x for x in self.project.route_plan if x != uid]
        if self.detail_route_uid == uid:
            self.detail_route_uid = self.project.route_plan[0] if self.project.route_plan else (self.project.routes[0].uid if self.project.routes else None)
        self.refresh_route_trees()
        self.clear_results(keep_analysis=False)

    def add_selected_available_to_plan(self):
        uid = self._selected_available_uid()
        if uid is None:
            return
        if uid not in self.project.route_plan:
            self.project.route_plan.append(uid)
            route = self._route_by_uid(uid)
            if route is not None:
                route.enabled = True
        self.refresh_route_trees()
        self._set_detail_route(uid)
        self.clear_results(keep_analysis=False)

    def remove_selected_plan_route(self):
        uid = self._selected_plan_uid() or self._selected_available_uid()
        if uid is None or uid not in self.project.route_plan:
            return
        self.project.route_plan = [x for x in self.project.route_plan if x != uid]
        route = self._route_by_uid(uid)
        if route is not None:
            route.enabled = False
        self.refresh_route_trees()
        self._set_detail_route(uid)
        self.clear_results(keep_analysis=False)

    def clear_plan(self):
        self.project.route_plan = []
        for route in self.project.routes:
            route.enabled = False
        self.refresh_route_trees()
        self.clear_results(keep_analysis=False)

    def move_selected_plan_route(self, delta: int):
        uid = self._selected_plan_uid()
        if uid is None or uid not in self.project.route_plan:
            return
        idx = self.project.route_plan.index(uid)
        new_idx = idx + delta
        if not (0 <= new_idx < len(self.project.route_plan)):
            return
        self.project.route_plan[idx], self.project.route_plan[new_idx] = self.project.route_plan[new_idx], self.project.route_plan[idx]
        self.refresh_route_trees()
        self._set_detail_route(uid)
        self.clear_results(keep_analysis=False)

    def remove_all_vanilla_from_plan(self):
        vanilla_ids = {route.uid for route in self.project.routes if route.is_vanilla}
        self.project.route_plan = [uid for uid in self.project.route_plan if uid not in vanilla_ids]
        for route in self.project.routes:
            if route.is_vanilla:
                route.enabled = False
        self.refresh_route_trees()
        self.clear_results(keep_analysis=False)

    def import_repo_project(self):
        path = filedialog.askdirectory(title="pokeemerald-expansion Projektordner auswählen")
        if not path:
            return
        repo_root = Path(path)
        if not (repo_root / "data" / "maps").exists():
            messagebox.showerror("Ungültiger Ordner", "Ich habe darin kein data/maps-Verzeichnis gefunden.")
            return
        try:
            parser = RepoParser(repo_root)
            routes, species_db = parser.parse()
        except Exception as exc:
            messagebox.showerror("Import fehlgeschlagen", f"Beim Import ist ein Fehler aufgetreten:\n{exc}")
            return

        existing_manual = [r for r in self.project.routes if not r.imported]
        previous_imported = {((r.source_map_path or ""), r.name): r for r in self.project.routes if r.imported}
        old_plan = list(self.project.route_plan)
        old_planned_ids = set(old_plan)

        for route in routes:
            previous = previous_imported.get(((route.source_map_path or ""), route.name))
            if previous is not None:
                route.uid = previous.uid or uuid4().hex
                route.is_vanilla = previous.is_vanilla
                route.enabled = previous.enabled
            else:
                route.uid = uuid4().hex
        for route in existing_manual:
            if not route.uid:
                route.uid = uuid4().hex

        self.project.routes = routes + existing_manual
        if species_db:
            self.project.species_db = species_db | self.project.species_db
        self.project.repo_root = str(repo_root)

        new_plan: list[str] = []
        if old_planned_ids:
            for route in self.project.routes:
                previous = previous_imported.get(((route.source_map_path or ""), route.name))
                if previous is not None and previous.uid in old_planned_ids:
                    new_plan.append(route.uid)
            for route in existing_manual:
                if route.uid in old_planned_ids and route.uid not in new_plan:
                    new_plan.append(route.uid)
        else:
            new_plan = [route.uid for route in self.project.routes if route.enabled and not route.is_vanilla]

        self.project.route_plan = new_plan
        self.repo_label_var.set(str(repo_root))
        self.refresh_all()
        self.clear_results()

        total = len(routes)
        custom = sum(1 for r in routes if not r.is_vanilla)
        planned = len(self.project.route_plan)
        messagebox.showinfo(
            "Import abgeschlossen",
            f"{total} Trainer-Maps importiert.\nDavon als Vanilla erkannt: {total - custom}\nIn die Berechnungsliste übernommen: {planned}",
        )

    # ---------- settings ----------
    def apply_preset(self, preset_name: str, from_user: bool):
        s = self.project.settings
        s.preset_name = preset_name
        if preset_name == "pokeemerald-expansion modern":
            s.use_scaled_exp = True
            s.trainer_multiplier = 1.0
            s.use_exp_share_for_bench = True
            s.bench_exp_factor = 0.5
            s.use_unevolved_bonus = True
            s.traded_bonus = 1.5
            s.lucky_egg_bonus = 1.5
        elif preset_name == "Emerald / Gen 3":
            s.use_scaled_exp = False
            s.trainer_multiplier = 1.5
            s.use_exp_share_for_bench = False
            s.bench_exp_factor = 0.5
            s.use_unevolved_bonus = False
            s.traded_bonus = 1.5
            s.lucky_egg_bonus = 1.5
        self.refresh_settings_form()
        if from_user:
            messagebox.showinfo("Preset übernommen", f"Preset „{preset_name}“ wurde geladen.")

    def pull_settings_from_form(self) -> bool:
        try:
            self.project.settings = PlannerSettings(
                preset_name=self.preset_var.get(),
                use_scaled_exp=self.scaled_var.get(),
                trainer_multiplier=float(self.trainer_mult_var.get()),
                use_exp_share_for_bench=self.exp_share_var.get(),
                bench_exp_factor=float(self.bench_factor_var.get()),
                use_unevolved_bonus=self.unevolved_bonus_var.get(),
                traded_bonus=float(self.traded_bonus_var.get()),
                lucky_egg_bonus=float(self.lucky_bonus_var.get()),
                suggestion_offset=float(self.suggestion_offset_var.get()),
                suggestion_spread=float(self.suggestion_spread_var.get()),
                ace_offset=float(self.ace_offset_var.get()),
            )
            return True
        except ValueError:
            messagebox.showerror("Ungültige Einstellungen", "Bitte nur gültige Zahlen in den Einstellungen eintragen.")
            return False

    # ---------- calculations ----------
    def calculate(self):
        if not self.pull_settings_from_form():
            return
        if not self.project.team:
            messagebox.showwarning("Team fehlt", "Bitte zuerst mindestens ein Team-Pokémon anlegen.")
            return
        plan_routes = self._plan_routes()
        if not plan_routes:
            messagebox.showwarning("Keine Berechnungsliste", "Bitte per Doppelklick oder Button mindestens eine Route in die Berechnungsliste aufnehmen.")
            return

        team_state: list[dict[str, Any]] = []
        for mon in self.project.team:
            exp_value = Growth.start_exp_from_level_and_progress(mon.growth_rate, mon.start_level, mon.level_progress_pct)
            team_state.append({"mon": mon, "exp": exp_value})

        results_rows: list[dict[str, Any]] = []
        route_csv_rows: list[list[str]] = []
        self._last_analysis_by_route_name = {}

        for route in plan_routes:
            before_levels = [Growth.level_from_exp(x["mon"].growth_rate, x["exp"]) for x in team_state]
            before_avg = mean(before_levels)
            total_route_gain = 0.0

            for trainer in route.trainers:
                for enemy in trainer.enemy_mons:
                    for idx, state in enumerate(team_state):
                        mon = state["mon"]
                        current_level = Growth.level_from_exp(mon.growth_rate, state["exp"])
                        rate = route.participation_rates[idx] if idx < len(route.participation_rates) else 0.0
                        gain = ExpEngine.expected_gain_for_mon(
                            enemy=enemy,
                            mon=mon,
                            current_level=current_level,
                            participation_rate=rate,
                            avg_active_battlers=route.avg_active_battlers,
                            settings=self.project.settings,
                        )
                        state["exp"] += gain
                        total_route_gain += gain

            after_levels = [Growth.level_from_exp(x["mon"].growth_rate, x["exp"]) for x in team_state]
            after_avg = mean(after_levels)
            avg_gain = after_avg - before_avg
            target_avg = after_avg + self.project.settings.suggestion_offset
            spread = self.project.settings.suggestion_spread
            suggested_range = f"{max(1, math.floor(target_avg - spread))}-{min(100, math.ceil(target_avg + spread))}"
            ace_level = max(1, min(100, round_half_down(target_avg + self.project.settings.ace_offset)))

            current_enemy_levels = [m.level for t in route.trainers for m in t.enemy_mons]
            enemy_avg = mean(current_enemy_levels) if current_enemy_levels else 1.0
            shift = target_avg - enemy_avg
            trainer_suggestions: dict[str, list[int]] = {}
            for trainer_idx, trainer in enumerate(route.trainers):
                levels: list[int] = []
                for mon in trainer.enemy_mons:
                    proposed = max(1, min(100, round_half_down(mon.level + shift)))
                    levels.append(proposed)
                if levels:
                    ace_pos = max(range(len(levels)), key=lambda i: levels[i])
                    levels[ace_pos] = max(levels[ace_pos], ace_level)
                trainer_suggestions[f"{trainer.name}#{trainer_idx}"] = levels

            analysis = {
                "enemy_avg": enemy_avg,
                "target_avg": target_avg,
                "range": suggested_range,
                "ace": ace_level,
                "trainer_suggestions": trainer_suggestions,
                "before": before_avg,
                "after": after_avg,
            }
            self._last_analysis_by_route_name[route.uid] = analysis

            results_rows.append({
                "uid": route.uid,
                "route": route.name,
                "before": before_avg,
                "after": after_avg,
                "gain": avg_gain,
                "enemy_avg": enemy_avg,
                "next_avg": target_avg,
                "range": suggested_range,
                "ace": ace_level,
            })
            route_csv_rows.append([
                route.name,
                f"{before_avg:.2f}",
                f"{after_avg:.2f}",
                f"{avg_gain:.2f}",
                f"{enemy_avg:.2f}",
                f"{target_avg:.2f}",
                suggested_range,
                str(ace_level),
                str(sum(len(t.enemy_mons) for t in route.trainers)),
                f"{total_route_gain:.0f}",
            ])

        self._render_results(results_rows, team_state)
        self._last_csv_rows = route_csv_rows
        self.notebook.select(self.results_tab)
        self.refresh_route_details()

    def _render_results(self, results_rows: list[dict[str, Any]], team_state: list[dict[str, Any]]):
        for item in self.result_tree.get_children():
            self.result_tree.delete(item)
        for row in results_rows:
            self.result_tree.insert("", "end", iid=row["uid"], values=(
                row["route"],
                f"{row['before']:.2f}",
                f"{row['after']:.2f}",
                f"{row['gain']:.2f}",
                f"{row['enemy_avg']:.2f}",
                f"{row['next_avg']:.2f}",
                row["range"],
                row["ace"],
            ))
        for item in self.final_team_tree.get_children():
            self.final_team_tree.delete(item)
        for idx, state in enumerate(team_state):
            mon: TeamMon = state["mon"]
            exp = state["exp"]
            level = Growth.level_from_exp(mon.growth_rate, exp)
            progress = Growth.progress_pct_from_exp(mon.growth_rate, exp)
            self.final_team_tree.insert("", "end", iid=str(idx), values=(mon.name, level, f"{progress:.1f}%", int(exp)))

        notes = [
            "Neuer Workflow:",
            "1. Links eine Map doppelklicken oder per Button in die Berechnungsliste aufnehmen.",
            "2. Rechts die Reihenfolge per Drag-and-drop oder Nach oben/Nach unten festlegen.",
            "3. Auf Berechnen klicken.",
            "4. Danach eine Route auswählen: In den Details siehst du jeden Trainer mit aktuellem und vorgeschlagenem Level.",
            "",
            "Wie die Vorschläge entstehen:",
            "1. Das Tool berechnet, auf welchem Team-Ø du nach einer Route ungefähr landest.",
            "2. Daraus entsteht ein Ziel-Ø für das nächste Gebiet.",
            "3. Die aktuellen Gegnerlevel dieser Route werden um denselben Durchschnitts-Shift verschoben.",
            "4. Das höchste Pokémon einer Route wird mindestens auf den Ace/Boss-Vorschlag gesetzt.",
            "",
            "Hinweis:",
            "- Nur die Berechnungsliste rechts fließt in die Levelkurve ein.",
            "- Eine importierte Map bleibt links sichtbar, auch wenn sie nicht in der Liste steht.",
            "- Mit dem Button oben kannst du die Vorschläge direkt auf die gewählte Route anwenden.",
        ]
        self.result_notes.configure(state="normal")
        self.result_notes.delete("1.0", "end")
        self.result_notes.insert("1.0", "\n".join(notes))
        self.result_notes.configure(state="disabled")

    def on_result_select(self, _event=None):
        selection = self.result_tree.selection()
        if not selection:
            return
        uid = selection[0]
        if self._route_by_uid(uid) is not None:
            self.detail_route_uid = uid
            self.notebook.select(self.routes_tab)
            self.refresh_route_trees()
            self.refresh_route_details()

    def apply_suggestions_to_selected_route(self):
        uid = self._selected_or_detail_uid()
        if uid is None:
            result_selection = self.result_tree.selection()
            if result_selection:
                uid = result_selection[0]
        route = self._route_by_uid(uid)
        if route is None:
            messagebox.showinfo("Keine Route ausgewählt", "Bitte zuerst eine Route in der Planung oder im Ergebnis auswählen.")
            return
        analysis = self._last_analysis_by_route_name.get(route.uid)
        if not analysis:
            messagebox.showinfo("Keine Vorschläge", "Bitte zuerst eine Berechnung durchführen.")
            return
        suggestions = analysis.get("trainer_suggestions", {})
        changed = 0
        for trainer_idx, trainer in enumerate(route.trainers):
            key = f"{trainer.name}#{trainer_idx}"
            levels = suggestions.get(key, [])
            for mon_idx, mon in enumerate(trainer.enemy_mons):
                if mon_idx < len(levels):
                    mon.level = int(levels[mon_idx])
                    changed += 1
        self.refresh_route_details()
        self.clear_results(keep_analysis=False)
        messagebox.showinfo("Vorschlag übernommen", f"{changed} Gegnerlevel in „{route.name}“ wurden auf die berechneten Werte gesetzt.")

    # ---------- persistence ----------
    def new_project(self):
        self.project = ProjectData()
        self.current_project_path = None
        self.detail_route_uid = None
        self.apply_preset(self.project.settings.preset_name, from_user=False)
        self.refresh_all()
        self.clear_results()

    def save_project(self):
        if self.current_project_path is None:
            self.save_project_as()
            return
        self._write_project_file(self.current_project_path)

    def save_project_as(self):
        if not self.pull_settings_from_form():
            return
        path = filedialog.asksaveasfilename(title="Projekt speichern", defaultextension=".json", filetypes=[("JSON", "*.json")])
        if not path:
            return
        self.current_project_path = Path(path)
        self._write_project_file(self.current_project_path)

    def _write_project_file(self, path: Path):
        if not self.pull_settings_from_form():
            return
        self.migrate_project_state()
        payload = safe_asdict(self.project)
        path.write_text(json.dumps(payload, indent=2, ensure_ascii=False), encoding="utf-8")
        messagebox.showinfo("Gespeichert", f"Projekt gespeichert:\n{path}")

    def load_project(self):
        path = filedialog.askopenfilename(title="Projekt laden", filetypes=[("JSON", "*.json")])
        if not path:
            return
        data = json.loads(Path(path).read_text(encoding="utf-8"))
        self.project = ProjectData(
            team=[dataclass_from_dict(TeamMon, x) for x in data.get("team", [])],
            routes=[dataclass_from_dict(RouteEntry, x) for x in data.get("routes", [])],
            route_plan=data.get("route_plan", []),
            settings=PlannerSettings(**data.get("settings", {})) if data.get("settings") else PlannerSettings(),
            species_db=data.get("species_db", {}),
            repo_root=data.get("repo_root", ""),
        )
        self.current_project_path = Path(path)
        self.detail_route_uid = None
        self.refresh_all()
        self.clear_results()
        messagebox.showinfo("Projekt geladen", f"Projekt geladen:\n{path}")

    def load_species_csv(self):
        path = filedialog.askopenfilename(title="Spezies-CSV laden", filetypes=[("CSV", "*.csv")])
        if not path:
            return
        species_db: dict[str, dict[str, Any]] = {}
        with open(path, "r", encoding="utf-8-sig", newline="") as f:
            reader = csv.DictReader(f)
            required = {"species", "base_exp", "growth_rate"}
            if not reader.fieldnames or not required.issubset({x.strip() for x in reader.fieldnames}):
                raise ValueError("CSV muss die Spalten species, base_exp, growth_rate enthalten.")
            for row in reader:
                species = (row.get("species") or "").strip()
                if not species:
                    continue
                species_db[normalize_key(species)] = {
                    "display_name": species,
                    "base_exp": int((row.get("base_exp") or "0").strip()),
                    "growth_rate": (row.get("growth_rate") or "Medium Slow").strip(),
                }
        self.project.species_db = species_db | self.project.species_db
        messagebox.showinfo("CSV geladen", f"{len(species_db)} Spezies aus CSV geladen.")

    def export_results_csv(self):
        rows = self._last_csv_rows
        if not rows:
            messagebox.showinfo("Keine Daten", "Bitte zuerst eine Berechnung durchführen.")
            return
        path = filedialog.asksaveasfilename(title="Routen-Zusammenfassung exportieren", defaultextension=".csv", filetypes=[("CSV", "*.csv")])
        if not path:
            return
        with open(path, "w", encoding="utf-8", newline="") as f:
            writer = csv.writer(f)
            writer.writerow([
                "route", "team_avg_before", "team_avg_after", "avg_gain", "current_enemy_avg", "suggested_next_avg",
                "suggested_standard_range", "suggested_ace_level", "enemy_count", "total_expected_exp"
            ])
            writer.writerows(rows)
        messagebox.showinfo("Exportiert", f"CSV exportiert:\n{path}")

    def clear_results(self, keep_analysis: bool = False):
        for widget in (self.result_tree, self.final_team_tree):
            for item in widget.get_children():
                widget.delete(item)
        self.result_notes.configure(state="normal")
        self.result_notes.delete("1.0", "end")
        self.result_notes.configure(state="disabled")
        self._last_csv_rows = None
        if not keep_analysis:
            self._last_analysis_by_route_name = {}
        self.refresh_route_details()

    # ---------- help ----------
    def show_help(self):
        msg = (
            "Dieses Tool kann aktuelle Expansion-Projekte direkt einlesen.\n\n"
            "Import-Funktion:\n"
            "- scannt data/maps/*/map.json\n"
            "- liest pro Objekt-Event trainer_type + script aus\n"
            "- sucht das passende TRAINER_... in Skriptdateien\n"
            "- liest Team, Klasse und Level aus src/data/trainers.party\n\n"
            "Planungs-Workflow:\n"
            "- links liegen alle importierten Maps\n"
            "- Doppelklick oder Pfeil fügt eine Map in die Berechnungsliste ein\n"
            "- rechts sortierst du diese Liste per Drag-and-drop\n"
            "- nur diese Reihenfolge wird berechnet\n\n"
            "Analyse:\n"
            "- berechnet Team-Ø vor/nach jeder Route der Berechnungsliste\n"
            "- zeigt aktuelle Gegnerlevel und vorgeschlagene neue Level pro Trainer an\n"
            "- Vorschläge lassen sich direkt auf die gewählte Route anwenden"
        )
        messagebox.showinfo("Hilfe / Annahmen", msg)

def main():
    app = PlannerApp()
    app.mainloop()


if __name__ == "__main__":
    main()
