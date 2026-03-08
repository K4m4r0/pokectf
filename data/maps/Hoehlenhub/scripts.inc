Hoehlenhub_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Hoehlenhub_OnTransition
    .byte 0


Hoehlenhub_OnTransition::
    setflag FLAG_ABSTELLKAMMER_DOLL_AWAY
    end



@ =========================================================
@ NPC dialogue
@ =========================================================
Hoehlenhub_EventScript_StormWarning::
    lock
    faceplayer
    msgbox Hoehlenhub_Text_StormWarning, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Text
@ =========================================================
Hoehlenhub_Text_StormWarning:
    .string "We can't go out yet, the storm is\n"
    .string "still too strong.$"

