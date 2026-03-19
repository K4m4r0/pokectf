#include "global.h"
#include "rotom_house.h"

#include "event_data.h"
#include "pokemon.h"
#include "constants/species.h"

static bool8 IsRotomFamilySpecies(u16 species)
{
    switch (species)
    {
    case SPECIES_ROTOM:
    case SPECIES_ROTOM_HEAT:
    case SPECIES_ROTOM_WASH:
    case SPECIES_ROTOM_FROST:
    case SPECIES_ROTOM_FAN:
    case SPECIES_ROTOM_MOW:
        return TRUE;
    default:
        return FALSE;
    }
}

void Special_RotomHouseChangeSelectedPartyRotomForm(void)
{
    u16 partyIndex = VarGet(VAR_0x8004);
    u16 targetSpecies = VarGet(VAR_0x8005);
    struct Pokemon *mon;
    u16 currentSpecies;
    u16 oldHp;
    u16 oldMaxHp;
    u16 newMaxHp;
    u16 newHp;

    if (partyIndex >= PARTY_SIZE)
    {
        gSpecialVar_Result = 0;
        return;
    }

    mon = &gPlayerParty[partyIndex];

    if (GetMonData(mon, MON_DATA_IS_EGG))
    {
        gSpecialVar_Result = 4;
        return;
    }

    currentSpecies = GetMonData(mon, MON_DATA_SPECIES);

    if (!IsRotomFamilySpecies(currentSpecies))
    {
        gSpecialVar_Result = 2;
        return;
    }

    if (!IsRotomFamilySpecies(targetSpecies))
    {
        gSpecialVar_Result = 2;
        return;
    }

    if (currentSpecies == targetSpecies)
    {
        gSpecialVar_Result = 3;
        return;
    }

    oldHp = GetMonData(mon, MON_DATA_HP);
    oldMaxHp = GetMonData(mon, MON_DATA_MAX_HP);

    SetMonData(mon, MON_DATA_SPECIES, &targetSpecies);
    CalculateMonStats(mon);

    newMaxHp = GetMonData(mon, MON_DATA_MAX_HP);

    if (oldMaxHp == 0)
    {
        newHp = newMaxHp;
    }
    else
    {
        newHp = (oldHp * newMaxHp) / oldMaxHp;
        if (oldHp > 0 && newHp == 0)
            newHp = 1;
    }

    SetMonData(mon, MON_DATA_HP, &newHp);

    gSpecialVar_Result = 1;
}