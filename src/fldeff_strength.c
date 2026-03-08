#include "global.h"
#include "event_data.h"
#include "event_scripts.h"
#include "field_effect.h"
#include "fldeff.h"
#include "party_menu.h"
#include "script.h"
#include "string_util.h"
#include "task.h"
#include "constants/event_objects.h"
#include "constants/field_effects.h"

// static functions
static void FieldCallback_Strength(void);
static void StartStrengthFieldEffect(void);
static bool32 IsStrengthObjectInFrontOfPlayer(void);

// text
static bool32 IsStrengthObjectInFrontOfPlayer(void)
{
    return CheckObjectGraphicsInFrontOfPlayer(OBJ_EVENT_GFX_PUSHABLE_BOULDER) == TRUE
        || CheckObjectGraphicsInFrontOfPlayer(OBJ_EVENT_GFX_MOVING_BOX) == TRUE
        || CheckObjectGraphicsInFrontOfPlayer(OBJ_EVENT_GFX_CD) == TRUE
        || CheckObjectGraphicsInFrontOfPlayer(OBJ_EVENT_GFX_BIG_CHARIZARD_DOLL) == TRUE;
}

bool32 SetUpFieldMove_Strength(void)
{
    if (IsStrengthObjectInFrontOfPlayer() == TRUE)
    {
        gSpecialVar_Result = GetCursorSelectionMonId();
        gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
        gPostMenuFieldCallback = FieldCallback_Strength;
        return TRUE;
    }
    return FALSE;
}

static void FieldCallback_Strength(void)
{
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
    ScriptContext_SetupScript(EventScript_UseStrength);
}

bool8 FldEff_UseStrength(void)
{
    u8 taskId = CreateFieldMoveTask();
    gTasks[taskId].data[8] = (u32)StartStrengthFieldEffect >> 16;
    gTasks[taskId].data[9] = (u32)StartStrengthFieldEffect;
    GetMonNickname(&gPlayerParty[gFieldEffectArguments[0]], gStringVar1);
    return FALSE;
}

// Just passes control back to EventScript_UseStrength
static void StartStrengthFieldEffect(void)
{
    FieldEffectActiveListRemove(FLDEFF_USE_STRENGTH);
    ScriptContext_Enable();
}