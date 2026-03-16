#ifndef GUARD_CTF_MEWTWO_BATTLE_H
#define GUARD_CTF_MEWTWO_BATTLE_H

#include "global.h"

const u8 *CtfMewtwoBattle_GetTurnScript(void);
void CtfMewtwoBattle_MarkPlayerMonKOByMewtwo(u32 battler);
bool8 CtfMewtwoBattle_ShouldInterceptPlayerFaint(u32 battler);
const u8 *CtfMewtwoBattle_GetPlayerFaintScript(u32 battler);
void CtfMewtwoBattle_ClearPendingPlayerFaint(u32 battler);
bool8 CtfMewtwoBattle_ShouldShowLossLine(void);
void CtfMewtwoBattle_End(void);

#endif