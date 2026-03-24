#include "global.h"
#include "event_data.h"      // VarGet / VarSet, VAR_* IDs
#include "pokemon.h"
#include "evolution_scene.h"
#include "script.h"
#include "constants/items.h"
#include "constants/vars.h"
#include "constants/pokemon.h"

// sorgt dafür, dass nach der Evolution wieder ins Script zurückgekehrt wird
extern void CB2_ReturnToFieldContinueScript(void);

enum
{
    FAKE_TRADE_OK = 1,
    FAKE_TRADE_WRONG_SPECIES = 2,
    FAKE_TRADE_IS_EGG = 3,
    FAKE_TRADE_EVERSTONE_BLOCK = 4,
    FAKE_TRADE_MISSING_HELD_ITEM = 5,
};

void Special_FakeTradeEvolveSelectedToTarget(void)
{
    u16 slot            = VarGet(VAR_0x8004);
    u16 targetSpecies   = VarGet(VAR_0x8006);
    bool8 consumeItem   = (VarGet(VAR_0x8009) != 0);

    struct Pokemon *mon;
    u16 heldItem;

    VarSet(VAR_RESULT, 0);

    if (slot >= PARTY_SIZE)
        return;

    mon = &gPlayerParty[slot];

    if (consumeItem)
    {
        u16 none = ITEM_NONE;
        heldItem = GetMonData(mon, MON_DATA_HELD_ITEM);
        if (heldItem != ITEM_NONE)
            SetMonData(mon, MON_DATA_HELD_ITEM, &none);
    }

    ScriptContext_Enable();
    gCB2_AfterEvolution = CB2_ReturnToFieldContinueScript;
    BeginEvolutionScene(mon, targetSpecies, FALSE, slot);

    VarSet(VAR_RESULT, FAKE_TRADE_OK);
}



void Special_FakeTradeCanSelectedToTarget(void)
{
    u16 slot              = VarGet(VAR_0x8004);
    u16 requiredSpecies   = VarGet(VAR_0x8005);
    u16 requiredItem      = VarGet(VAR_0x8007);
    bool8 ignoreEverstone = (VarGet(VAR_0x8008) != 0);

    struct Pokemon *mon;
    u16 species;
    u16 heldItem;

    VarSet(VAR_RESULT, 0);

    if (slot >= PARTY_SIZE)
    {
        VarSet(VAR_RESULT, FAKE_TRADE_WRONG_SPECIES);
        return;
    }

    mon = &gPlayerParty[slot];

    if (GetMonData(mon, MON_DATA_IS_EGG))
    {
        VarSet(VAR_RESULT, FAKE_TRADE_IS_EGG);
        return;
    }

    species = GetMonData(mon, MON_DATA_SPECIES);
    if (species != requiredSpecies)
    {
        VarSet(VAR_RESULT, FAKE_TRADE_WRONG_SPECIES);
        return;
    }

    heldItem = GetMonData(mon, MON_DATA_HELD_ITEM);

    if (!ignoreEverstone && heldItem == ITEM_EVERSTONE)
    {
        VarSet(VAR_RESULT, FAKE_TRADE_EVERSTONE_BLOCK);
        return;
    }

    if (requiredItem != ITEM_NONE && requiredItem != 0 && heldItem != requiredItem)
    {
        VarSet(VAR_RESULT, FAKE_TRADE_MISSING_HELD_ITEM);
        return;
    }

    VarSet(VAR_RESULT, FAKE_TRADE_OK);
}