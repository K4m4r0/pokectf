Zwischenstueck_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Zwischenstueck_OnTransition
    .byte 0

Zwischenstueck_OnTransition:
    call Zwischenstueck_DayCare_OnTransition
    call Zwischenstueck_Guard_OnTransition
    end

@ -----------------------
@ Daycare Außenlogik
@ -----------------------
Zwischenstueck_DayCare_OnTransition:
    call Zwischenstueck_TryMoveDayCareMan

    setflag FLAG_TEMP_1
    setflag FLAG_TEMP_2
    getdaycaregfx VAR_OBJ_GFX_ID_0, VAR_OBJ_GFX_ID_1, VAR_TEMP_0, VAR_TEMP_1
    switch VAR_RESULT
    case 2, Zwischenstueck_ShowDaycareMon1
    case 1, Zwischenstueck_ShowDaycareMon0
    end
    return

Zwischenstueck_ShowDaycareMon1:
    special SetDaycareCompatibilityString
    call_if_eq VAR_RESULT, PARENTS_INCOMPATIBLE, Zwischenstueck_DaycareMonIncompatible
    call_if_eq VAR_RESULT, PARENTS_MED_COMPATIBILITY, Zwischenstueck_DaycareMonMedCompatibility
    call_if_eq VAR_RESULT, PARENTS_MAX_COMPATIBILITY, Zwischenstueck_DaycareMonMaxCompatibility
    clearflag FLAG_TEMP_2
Zwischenstueck_ShowDaycareMon0:
    clearflag FLAG_TEMP_1
    return

Zwischenstueck_DaycareMonIncompatible:
    setobjectmovementtype LOCALID_DAYCARE_MON_0, MOVEMENT_TYPE_FACE_DOWN_UP_AND_LEFT
    setobjectmovementtype LOCALID_DAYCARE_MON_1, MOVEMENT_TYPE_FACE_DOWN_UP_AND_RIGHT
    return

Zwischenstueck_DaycareMonMedCompatibility:
    setobjectmovementtype LOCALID_DAYCARE_MON_0, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT
    setobjectmovementtype LOCALID_DAYCARE_MON_1, MOVEMENT_TYPE_FACE_DOWN_AND_LEFT
    return

Zwischenstueck_DaycareMonMaxCompatibility:
    setobjectmovementtype LOCALID_DAYCARE_MON_0, MOVEMENT_TYPE_WALK_IN_PLACE_RIGHT
    setobjectmovementtype LOCALID_DAYCARE_MON_1, MOVEMENT_TYPE_WALK_IN_PLACE_LEFT
    return

Zwischenstueck_TryMoveDayCareMan:
    goto_if_unset FLAG_PENDING_DAYCARE_EGG, Zwischenstueck_ResetDayCareMan
    setobjectxyperm LOCALID_DAYCARE_MAN, 11, 8
    return

Zwischenstueck_ResetDayCareMan:
    setobjectxyperm LOCALID_DAYCARE_MAN, 11, 6
    return

Zwischenstueck_StopMoveDayCareMan:
    return


@ =========================================================
@ Object: Password Guard
@ =========================================================

Zwischenstueck_EventScript_PasswordGuard::
    lock

    @ After moved -> always same line, keep facing down
    goto_if_set FLAG_ZWISCHENSTUECK_GUARD_MOVED, Zwischenstueck_Guard_After

    faceplayer

    @ If player hasn't done the tap yet -> get lost
    goto_if_unset FLAG_BLACKHANSA_SERVER_TAP_DONE, Zwischenstueck_Guard_NoPassword

    @ Success path (flag set): say the 3 lines
    msgbox Zwischenstueck_Text_Pass_Question, MSGBOX_DEFAULT
    msgbox Zwischenstueck_Text_Pass_Answer,   MSGBOX_DEFAULT
    msgbox Zwischenstueck_Text_Pass_Ok,       MSGBOX_DEFAULT
    closemessage

    @ Move 1 tile right, then face down
    applymovement LOCALID_PASSWORD_GUARD, Zwischenstueck_Movement_Guard_Right1FaceDown
    waitmovement 0

    @ Make it permanent for future visits
    setflag FLAG_ZWISCHENSTUECK_GUARD_MOVED

    release
    end

Zwischenstueck_Guard_NoPassword:
    msgbox Zwischenstueck_Text_NoPassword, MSGBOX_DEFAULT
    release
    end

Zwischenstueck_Guard_After:
    msgbox Zwischenstueck_Text_AfterMoved, MSGBOX_DEFAULT
    turnobject LOCALID_PASSWORD_GUARD, DIR_WEST
    release
    end

Zwischenstueck_Guard_OnTransition:
    goto_if_unset FLAG_ZWISCHENSTUECK_GUARD_MOVED, Zwischenstueck_Guard_Trans_Return
    setobjectxyperm LOCALID_PASSWORD_GUARD, 10, 16   @ Start war 9,16 -> nach rechts 1
    turnobject LOCALID_PASSWORD_GUARD, DIR_WEST      @ oder DIR_SOUTH, wie du willst
Zwischenstueck_Guard_Trans_Return:
    return


@ =========================================================
@ Movement
@ =========================================================

Zwischenstueck_Movement_Guard_Right1FaceDown:
    walk_right
    face_left
    step_end


@ =========================================================
@ Text
@ =========================================================

Zwischenstueck_Text_NoPassword:
    .string "Do you have the password?\n"
    .string "If not, get lost!$"

Zwischenstueck_Text_Pass_Question:
    .string "Do you have the password?$"

Zwischenstueck_Text_Pass_Answer:
    .string "Yes, it's CASSEROLE$"

Zwischenstueck_Text_Pass_Ok:
    .string "All right.$"

Zwischenstueck_Text_AfterMoved:
    .string "Mind your own business.$"



Zwischenstueck_EventScript_Sign::
	msgbox Zwischenstueck_Text_TownSign, MSGBOX_SIGN
	end

Zwischenstueck_EventScript_Lagerhaus::
	msgbox Zwischenstueck_Text_Lagerhaus, MSGBOX_SIGN
	end

Zwischenstueck_Text_TownSign::
	.string "Left: DHBW\n"
	.string "Right: JUNGBUSCH$"

Zwischenstueck_Text_Lagerhaus::
	.string " Old BLACKHANSA warehouse.$"

