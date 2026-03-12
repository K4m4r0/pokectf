LugiaSpawn_MapScripts::
	map_script MAP_SCRIPT_ON_DIVE_WARP, LugiaSpawn_OnDiveWarp
	.byte 0

LugiaSpawn_OnDiveWarp:
	getplayerxy VAR_0x8004, VAR_0x8005
	call LugiaSpawn_EventScript_SetDiveWarpToSurface
	end

LugiaSpawn_EventScript_SurfaceSpot::
	getplayerxy VAR_0x8004, VAR_0x8005
	call LugiaSpawn_EventScript_SetDiveWarpToSurface
	goto EventScript_UseDiveUnderwater

LugiaSpawn_EventScript_SetDiveWarpToSurface::
	compare VAR_0x8004, 10
	goto_if_eq LugiaSpawn_EventScript_SetDiveWarpX10
	compare VAR_0x8004, 11
	goto_if_eq LugiaSpawn_EventScript_SetDiveWarpX11
	return

LugiaSpawn_EventScript_SetDiveWarpX10::
	compare VAR_0x8005, 32
	goto_if_eq LugiaSpawn_EventScript_SetDiveWarpSurfaceTL
	compare VAR_0x8005, 33
	goto_if_eq LugiaSpawn_EventScript_SetDiveWarpSurfaceBL
	return

LugiaSpawn_EventScript_SetDiveWarpX11::
	compare VAR_0x8005, 32
	goto_if_eq LugiaSpawn_EventScript_SetDiveWarpSurfaceTR
	compare VAR_0x8005, 33
	goto_if_eq LugiaSpawn_EventScript_SetDiveWarpSurfaceBR
	return

LugiaSpawn_EventScript_SetDiveWarpSurfaceTL::
	setdivewarp MAP_WAY_TO_CAFERTERIA, 61, 14
	return

LugiaSpawn_EventScript_SetDiveWarpSurfaceBL::
	setdivewarp MAP_WAY_TO_CAFERTERIA, 61, 15
	return

LugiaSpawn_EventScript_SetDiveWarpSurfaceTR::
	setdivewarp MAP_WAY_TO_CAFERTERIA, 62, 14
	return

LugiaSpawn_EventScript_SetDiveWarpSurfaceBR::
	setdivewarp MAP_WAY_TO_CAFERTERIA, 62, 15
	return
