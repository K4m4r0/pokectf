CH3_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, CH3_OnLoad
    .byte 0

    .equ CH3_OPEN_TOP_TILE, 0x202


@ =========================================================
@ OnLoad: Weg offen halten, wenn Gwen besiegt wurde
@ =========================================================
CH3_OnLoad:
    checktrainerflag TRAINER_GWEN
    goto_if_eq VAR_RESULT, TRUE, CH3_OpenPassage
    end

CH3_OpenPassage:
    setmetatile 9, 2, CH3_OPEN_TOP_TILE, FALSE
    special DrawWholeMapView
    end


@ =========================================================
@ DUDE
@ =========================================================
CH3_EventScript_Dude::
    lock
    faceplayer

    checktrainerflag TRAINER_GWEN
    goto_if_eq VAR_RESULT, TRUE, CH3_EventScript_Dude_After

    msgbox CH3_Text_DudeIntro, MSGBOX_DEFAULT
    closemessage

    trainerbattle_single TRAINER_GWEN, CH3_Text_DudeBattleIntro, CH3_Text_DudeBattleDefeat, CH3_EventScript_Dude_AfterBattle
    end

CH3_EventScript_Dude_AfterBattle::
    msgbox CH3_Text_DudeAfterBattle, MSGBOX_DEFAULT
    closemessage

    setmetatile 9, 2, CH3_OPEN_TOP_TILE, FALSE
    special DrawWholeMapView

    releaseall
    end

CH3_EventScript_Dude_After::
    msgbox CH3_Text_DudeAfter, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Texte
@ =========================================================
CH3_Text_DudeIntro:
    .string "DUDE: Room three.\p"
    .string "By now you should understand what\n"
    .string "the Challenge House is about.\p"
    .string "Only the players who stay focused\n"
    .string "make it to the end.$"

CH3_Text_DudeBattleIntro:
    .string "DUDE: Let's find out whether you\n"
    .string "still have what it takes.$"

CH3_Text_DudeBattleDefeat:
    .string "DUDE: Solid. You may move on.$"

CH3_Text_DudeAfterBattle:
    .string "DUDE: Nice work.\p"
    .string "The path to the next room is open.$"

CH3_Text_DudeAfter:
    .string "DUDE: Don't slow down now.\p"
    .string "The later rooms hit harder.$"

