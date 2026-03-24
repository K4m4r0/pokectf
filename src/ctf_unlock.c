#include "global.h"
#include "ctf_unlock.h"
#include "event_data.h"

EWRAM_DATA u16 gCtfVendorUnlockMagic = 0;

#define CTF_VENDOR_MAGIC 0xC7F7

// Rückgabewerte über VAR_RESULT / gSpecialVar_Result:
// 0 = noch gesperrt
// 1 = schon dauerhaft freigeschaltet
// 2 = gerade jetzt neu freigeschaltet
void CheckConsumeCtfVendorUnlock(void)
{
    if (FlagGet(FLAG_CTF_VENDOR_UNLOCKED))
    {
        gSpecialVar_Result = 1;
        gCtfVendorUnlockMagic = 0;
        return;
    }

    if (gCtfVendorUnlockMagic == CTF_VENDOR_MAGIC)
    {
        FlagSet(FLAG_CTF_VENDOR_UNLOCKED);
        gCtfVendorUnlockMagic = 0;
        gSpecialVar_Result = 2;
        return;
    }

    gSpecialVar_Result = 0;
}