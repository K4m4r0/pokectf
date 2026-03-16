#include "global.h"
#include "ctf_mewtwo_battle.h"
#include "event_data.h"
#include "battle.h"
#include "battle_scripts.h"
#include "constants/flags.h"
#include "constants/species.h"

static EWRAM_DATA bool8 sTurnTauntShown[16] = {0};
static EWRAM_DATA s8 sPendingPlayerFaintBattler;
static EWRAM_DATA bool8 sLossLineShown = FALSE;
static EWRAM_DATA bool8 sInitialized = FALSE;

static void InitIfNeeded(void)
{
    u32 i;

    if (sInitialized)
        return;

    for (i = 0; i < 16; i++)
        sTurnTauntShown[i] = FALSE;

    sPendingPlayerFaintBattler = -1;
    sLossLineShown = FALSE;
    sInitialized = TRUE;
}

static bool8 IsSpecialMewtwoBattle(void)
{
    return FlagGet(FLAG_MEWTWO_LAIR_SPECIAL_BATTLE);
}

static bool8 IsLivingMewtwoOnField(void)
{
    u32 i;
    for (i = 0; i < gBattlersCount; i++)
    {
        if (!(gAbsentBattlerFlags & (1u << i))
         && gBattleMons[i].species == SPECIES_MEWTWO
         && gBattleMons[i].hp != 0)
            return TRUE;
    }
    return FALSE;
}

static const u8 *GetTurnScriptByTurn(u16 turn)
{
    switch (turn)
    {
    case 3:  return BattleScript_MewtwoTurn3;
    case 5:  return BattleScript_MewtwoTurn5;
    case 7:  return BattleScript_MewtwoTurn7;
    case 9:  return BattleScript_MewtwoTurn9;
    case 12: return BattleScript_MewtwoTurn12;
    case 15: return BattleScript_MewtwoTurn15;
    default: return NULL;
    }
}

static const u8 *GetPatheticTurnScriptByTurn(u16 turn)
{
    switch (turn)
    {
    case 3:  return BattleScript_MewtwoPatheticTurn3;
    case 5:  return BattleScript_MewtwoPatheticTurn5;
    case 7:  return BattleScript_MewtwoPatheticTurn7;
    case 9:  return BattleScript_MewtwoPatheticTurn9;
    case 12: return BattleScript_MewtwoPatheticTurn12;
    case 15: return BattleScript_MewtwoPatheticTurn15;
    default: return BattleScript_MewtwoPathetic;
    }
}

const u8 *CtfMewtwoBattle_GetTurnScript(void)
{
    const u8 *script;

    if (!IsSpecialMewtwoBattle())
        return NULL;

    InitIfNeeded();

    if (!IsLivingMewtwoOnField())
        return NULL;

    if (gBattleTurnCounter >= 16)
        return NULL;

    if (sPendingPlayerFaintBattler != -1)
        return NULL;

    if (sTurnTauntShown[gBattleTurnCounter])
        return NULL;

    script = GetTurnScriptByTurn(gBattleTurnCounter);
    if (script == NULL)
        return NULL;

    sTurnTauntShown[gBattleTurnCounter] = TRUE;
    return script;
}

void CtfMewtwoBattle_MarkPlayerMonKOByMewtwo(u32 battler)
{
    if (!IsSpecialMewtwoBattle())
        return;

    InitIfNeeded();

    if (!IsOnPlayerSide(battler))
        return;

    sPendingPlayerFaintBattler = battler;
}


bool8 CtfMewtwoBattle_ShouldInterceptPlayerFaint(u32 battler)
{
    if (!IsSpecialMewtwoBattle())
        return FALSE;

    InitIfNeeded();

    if (!IsOnPlayerSide(battler))
        return FALSE;

    return (sPendingPlayerFaintBattler == battler);
}

const u8 *CtfMewtwoBattle_GetPlayerFaintScript(u32 battler)
{
    if (!CtfMewtwoBattle_ShouldInterceptPlayerFaint(battler))
        return NULL;

    InitIfNeeded();

    if (gBattleTurnCounter < 16 && !sTurnTauntShown[gBattleTurnCounter])
    {
        const u8 *turnScript = GetTurnScriptByTurn(gBattleTurnCounter);
        if (turnScript != NULL)
        {
            sTurnTauntShown[gBattleTurnCounter] = TRUE;
            return GetPatheticTurnScriptByTurn(gBattleTurnCounter);
        }
    }

    return BattleScript_MewtwoPathetic;
}

void CtfMewtwoBattle_ClearPendingPlayerFaint(u32 battler)
{
    if (sPendingPlayerFaintBattler == battler)
        sPendingPlayerFaintBattler = -1;
}

bool8 CtfMewtwoBattle_ShouldShowLossLine(void)
{
    if (!IsSpecialMewtwoBattle())
        return FALSE;

    InitIfNeeded();

    if (sLossLineShown)
        return FALSE;

    sLossLineShown = TRUE;
    return TRUE;
}

void CtfMewtwoBattle_End(void)
{
    u32 i;

    for (i = 0; i < 16; i++)
        sTurnTauntShown[i] = FALSE;

    sPendingPlayerFaintBattler = -1;
    sLossLineShown = FALSE;
    sInitialized = FALSE;
    FlagClear(FLAG_MEWTWO_LAIR_SPECIAL_BATTLE);
}
