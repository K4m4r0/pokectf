#ifndef GUARD_CTF_FLAGS_H
#define GUARD_CTF_FLAGS_H

#include "global.h"

#define CTF_GYM_COUNT 8
#define CTF_FLAG_TUTORIAL        (CTF_GYM_COUNT + 1)
#define CTF_FLAG_FINAL_FARMER    (CTF_GYM_COUNT + 2)
#define CTF_FLAG_FINAL_CLASSROOM (CTF_GYM_COUNT + 3)
#define CTF_FLAG_ENROLLMENT      (CTF_GYM_COUNT + 4)
#define CTF_FLAG_COUNT           CTF_FLAG_ENROLLMENT

// Neu: generische Prüfung für 1..CTF_FLAG_COUNT
bool8 Ctf_IsFlagCorrect(u8 flagId, const u8 *input);

// Alt lassen (Kompatibilität): prüft nur Gym 1..8
bool8 Ctf_IsGymFlagCorrect(u8 gymId, const u8 *input);

void Ctf_GetFlagWordUpper(u8 flagId, u8 *dst, u32 dstSize);
void Ctf_GetFlagSolutionString(u8 flagId, u8 *dst, u32 dstSize);

#endif // GUARD_CTF_FLAGS_H
