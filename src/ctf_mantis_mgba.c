#include <stdint.h>

extern uint16_t gSpecialVar_Result;
extern uint16_t gSpecialVar_0x8004;
extern uint8_t  gStringVar1[];

// Funktion existiert in src/ctf_flags.c
void Ctf_GetFlagSolutionString(uint8_t flagId, uint8_t *dst, uint32_t dstSize);

// mGBA debug pseudo-registers
#define REG_DEBUG_ENABLE (*(volatile uint16_t *)0x04FFF780)
#define REG_DEBUG_FLAGS  (*(volatile uint16_t *)0x04FFF700)
#define REG_DEBUG_STRING ((volatile char *)0x04FFF600)

static uint8_t MgbaOpen(void)
{
    REG_DEBUG_ENABLE = 0xC0DE;
    return (REG_DEBUG_ENABLE == 0x1DEA) ? 1 : 0;
}

static void MgbaLogString(uint8_t level, const char *msg)
{
    if (!MgbaOpen())
        return;

    uint32_t i = 0;
    while (i < 0xFF && msg[i] != '\0')
    {
        REG_DEBUG_STRING[i] = msg[i];
        i++;
    }
    REG_DEBUG_STRING[i] = '\0';
    REG_DEBUG_FLAGS = (level & 7) | 0x100; // string ready
}

// --- Specials (werden in data/specials.inc registriert) ---

void CtfIsMgba(void)
{
    gSpecialVar_Result = MgbaOpen();
}

void CtfMgbaLogHint_Flag5(void)
{
    MgbaLogString(2, "[MANTIS] entryMapFlag7: Suche 16-bit 0xBEEF (EWRAM) und patche auf 0x1337.");
}

void CtfBufferFlagSolution(void)
{
    // Flagwort ist max 7 Zeichen + EOS -> 16 ist mehr als genug
    Ctf_GetFlagSolutionString((uint8_t)gSpecialVar_0x8004, gStringVar1, 16);
}