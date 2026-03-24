HallwayHub_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, HallwayHub_OnLoad
    map_script MAP_SCRIPT_ON_TRANSITION, HallwayHub_OnTransition
    map_script MAP_SCRIPT_ON_FRAME_TABLE, HallwayHub_OnFrame
    .byte 0


@ ---------------------------------------------------------
@ OnLoad: neue Passage oben nach dem Sootopolis-Abschnitt freischalten
@ ---------------------------------------------------------
HallwayHub_OnLoad::
    goto_if_unset FLAG_DEFEATED_SOOTOPOLIS_GYM, HallwayHub_OnLoad_End

    setmetatile 13, 0, 0x202, TRUE
    setmetatile 13, 1, 0x20A, TRUE
    setmetatile 14, 0, 0x203, TRUE
    setmetatile 14, 1, 0x219, FALSE
    setmetatile 15, 0, 0x203, TRUE
    setmetatile 15, 1, 0x219, FALSE
    setmetatile 16, 0, 0x204, TRUE
    setmetatile 16, 1, 0x20C, TRUE
    special DrawWholeMapView

HallwayHub_OnLoad_End:
    end


@ ---------------------------------------------------------
@ OnTransition:
@ - Progress-Var aktualisieren
@ - welche einmalige Cutscene als nächstes laufen soll in VAR_TEMP_0 schreiben
@ ---------------------------------------------------------
HallwayHub_OnTransition::
    call HallwayHub_UpdateStage

    @ Default: keine Cutscene
    setvar VAR_TEMP_0, 99

    @ Höchste Priorität: neue Endsemester-Szene nach Sootopolis
    goto_if_set FLAG_DEFEATED_SOOTOPOLIS_GYM, HallwayHub_Check_Sem9

    @ Danach regulär weiter
    goto_if_set FLAG_DEFEATED_MOSSDEEP_GYM,   HallwayHub_Check_Sem8
    goto_if_set FLAG_DEFEATED_FORTREE_GYM,    HallwayHub_Check_Sem7
    goto_if_set FLAG_DEFEATED_PETALBURG_GYM,  HallwayHub_Check_Sem6
    goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM,  HallwayHub_Check_Sem5
    goto_if_set FLAG_DEFEATED_MAUVILLE_GYM,   HallwayHub_Check_Sem4
    goto_if_set FLAG_DEFEATED_DEWFORD_GYM,    HallwayHub_Check_Sem3
    goto_if_set FLAG_DEFEATED_RUSTBORO_GYM,   HallwayHub_Check_Sem2

    @ Intro – nur wenn noch nie abgespielt
    goto_if_set FLAG_HH_SEM1_DONE, HallwayHub_Transition_End
    setvar VAR_TEMP_0, 1
    end

HallwayHub_Check_Sem2:
    goto_if_set FLAG_HH_SEM2_DONE, HallwayHub_Transition_End
    setvar VAR_TEMP_0, 2
    end

HallwayHub_Check_Sem3:
    goto_if_set FLAG_HH_SEM3_DONE, HallwayHub_Transition_End
    setvar VAR_TEMP_0, 3
    end

HallwayHub_Check_Sem4:
    goto_if_set FLAG_HH_SEM4_DONE, HallwayHub_Transition_End
    setvar VAR_TEMP_0, 4
    end

HallwayHub_Check_Sem5:
    goto_if_set FLAG_HH_SEM5_DONE, HallwayHub_Transition_End
    setvar VAR_TEMP_0, 5
    end

HallwayHub_Check_Sem6:
    goto_if_set FLAG_HH_SEM6_DONE, HallwayHub_Transition_End
    setvar VAR_TEMP_0, 6
    end

HallwayHub_Check_Sem7:
    goto_if_set FLAG_HH_SEM7_DONE, HallwayHub_Transition_End
    setvar VAR_TEMP_0, 7
    end

HallwayHub_Check_Sem8:
    goto_if_set FLAG_HH_SEM8_DONE, HallwayHub_Transition_End
    setvar VAR_TEMP_0, 8
    end

HallwayHub_Check_Sem9:
    goto_if_set FLAG_HH_SEM9_DONE, HallwayHub_Transition_End
    setvar VAR_TEMP_0, 9
    end

HallwayHub_Transition_End:
    end


HallwayHub_OnFrame::
    map_script_2 VAR_TEMP_0, 1, HallwayHub_Scene_Sem1
    map_script_2 VAR_TEMP_0, 2, HallwayHub_Scene_Sem2
    map_script_2 VAR_TEMP_0, 3, HallwayHub_Scene_Sem3
    map_script_2 VAR_TEMP_0, 4, HallwayHub_Scene_Sem4
    map_script_2 VAR_TEMP_0, 5, HallwayHub_Scene_Sem5
    map_script_2 VAR_TEMP_0, 6, HallwayHub_Scene_Sem6
    map_script_2 VAR_TEMP_0, 7, HallwayHub_Scene_Sem7
    map_script_2 VAR_TEMP_0, 8, HallwayHub_Scene_Sem8
    map_script_2 VAR_TEMP_0, 9, HallwayHub_Scene_Sem9
    .2byte 0


@ ---------------------------------------------------------
@ Stage-Var setzen (0..8), damit du Warps per Coord-Events sperren kannst
@ 0 = nur Intro-Warp (x0,y4)
@ 1 = Rustboro frei (x5,y1)
@ 2 = Dewford frei (x8,y1)
@ 3 = Mauville frei (x11,y1)
@ 4 = Lavaridge frei (x18,y1)
@ 5 = Petalburg frei (x21,y1)
@ 6 = Fortree frei (x24,y1)
@ 7 = Mossdeep / Finale frei (x29,y4)
@ 8 = obere Passage frei (x14,y1 / x15,y1)
@ ---------------------------------------------------------
HallwayHub_UpdateStage::
    setvar VAR_HALLWAYHUB_STAGE, 0

    goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, 1f
    return
1:
    setvar VAR_HALLWAYHUB_STAGE, 1
    goto_if_set FLAG_DEFEATED_DEWFORD_GYM, 2f
    return
2:
    setvar VAR_HALLWAYHUB_STAGE, 2
    goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, 3f
    return
3:
    setvar VAR_HALLWAYHUB_STAGE, 3
    goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, 4f
    return
4:
    setvar VAR_HALLWAYHUB_STAGE, 4
    goto_if_set FLAG_DEFEATED_PETALBURG_GYM, 5f
    return
5:
    setvar VAR_HALLWAYHUB_STAGE, 5
    goto_if_set FLAG_DEFEATED_FORTREE_GYM, 6f
    return
6:
    setvar VAR_HALLWAYHUB_STAGE, 6
    goto_if_set FLAG_DEFEATED_MOSSDEEP_GYM, 7f
    return
7:
    setvar VAR_HALLWAYHUB_STAGE, 7
    goto_if_set FLAG_DEFEATED_SOOTOPOLIS_GYM, 8f
    return
8:
    setvar VAR_HALLWAYHUB_STAGE, 8
    return


@ =========================
@ Szenen (laufen je 1x)
@ =========================
HallwayHub_Scene_Sem1::
    setvar VAR_TEMP_0, 99
    setflag FLAG_HH_SEM1_DONE
    lockall
    msgbox HallwayHub_Text_Sem1, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, HallwayHub_Move_Sem1
    waitmovement 0
    releaseall
    warpsilent MAP_KLASSENZIMMER, 1, 0, 0
    waitstate
    end

HallwayHub_Scene_Sem2::
    setvar VAR_TEMP_0, 99
    setflag FLAG_HH_SEM1_DONE
    setflag FLAG_HH_SEM2_DONE
    lockall
    msgbox HallwayHub_Text_Sem2, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, HallwayHub_Move_Sem2
    waitmovement 0
    releaseall
    warpsilent MAP_HOUVERT_CLASS, 1, 0, 0
    waitstate
    end

HallwayHub_Scene_Sem3::
    setvar VAR_TEMP_0, 99
    setflag FLAG_HH_SEM1_DONE
    setflag FLAG_HH_SEM2_DONE
    setflag FLAG_HH_SEM3_DONE
    lockall
    msgbox HallwayHub_Text_Sem3, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, HallwayHub_Move_Sem3
    waitmovement 0
    releaseall
    warpsilent MAP_KLASSENZIMMER_SO_EN, 1, 0, 0
    waitstate
    end

HallwayHub_Scene_Sem4::
    setvar VAR_TEMP_0, 99
    setflag FLAG_HH_SEM1_DONE
    setflag FLAG_HH_SEM2_DONE
    setflag FLAG_HH_SEM3_DONE
    setflag FLAG_HH_SEM4_DONE
    lockall
    msgbox HallwayHub_Text_Sem4, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, HallwayHub_Move_Sem4
    waitmovement 0
    releaseall
    warpsilent MAP_KLASSENZIMMER_4, 1, 0, 0
    waitstate
    end

HallwayHub_Scene_Sem5::
    setvar VAR_TEMP_0, 99
    setflag FLAG_HH_SEM1_DONE
    setflag FLAG_HH_SEM2_DONE
    setflag FLAG_HH_SEM3_DONE
    setflag FLAG_HH_SEM4_DONE
    setflag FLAG_HH_SEM5_DONE
    lockall
    msgbox HallwayHub_Text_Sem5, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, HallwayHub_Move_Sem5
    waitmovement 0
    releaseall
    warpsilent MAP_KLASSENZIMMER5, 0, 0, 0
    waitstate
    end

HallwayHub_Scene_Sem6::
    setvar VAR_TEMP_0, 99
    setflag FLAG_HH_SEM1_DONE
    setflag FLAG_HH_SEM2_DONE
    setflag FLAG_HH_SEM3_DONE
    setflag FLAG_HH_SEM4_DONE
    setflag FLAG_HH_SEM5_DONE
    setflag FLAG_HH_SEM6_DONE
    lockall
    msgbox HallwayHub_Text_Sem6, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, HallwayHub_Move_Sem6
    waitmovement 0
    releaseall
    warpsilent MAP_KLASSENZIMMER6, 0, 0, 0
    waitstate
    end

HallwayHub_Scene_Sem7::
    setvar VAR_TEMP_0, 99
    setflag FLAG_HH_SEM1_DONE
    setflag FLAG_HH_SEM2_DONE
    setflag FLAG_HH_SEM3_DONE
    setflag FLAG_HH_SEM4_DONE
    setflag FLAG_HH_SEM5_DONE
    setflag FLAG_HH_SEM6_DONE
    setflag FLAG_HH_SEM7_DONE
    lockall
    msgbox HallwayHub_Text_Sem7, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, HallwayHub_Move_Sem7
    waitmovement 0
    releaseall
    warpsilent MAP_KLASSENZIMMER_FLAG7, 0, 0, 0
    waitstate
    end

HallwayHub_Scene_Sem8::
    setvar VAR_TEMP_0, 99
    setflag FLAG_HH_SEM1_DONE
    setflag FLAG_HH_SEM2_DONE
    setflag FLAG_HH_SEM3_DONE
    setflag FLAG_HH_SEM4_DONE
    setflag FLAG_HH_SEM5_DONE
    setflag FLAG_HH_SEM6_DONE
    setflag FLAG_HH_SEM7_DONE
    setflag FLAG_HH_SEM8_DONE
    lockall
    msgbox HallwayHub_Text_Sem8, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, HallwayHub_Move_Sem8
    waitmovement 0
    releaseall
    warpsilent MAP_KLASSENZIMMER_FINALE, 0, 0, 0
    waitstate
    end

HallwayHub_Scene_Sem9::
    setvar VAR_TEMP_0, 99
    setflag FLAG_HH_SEM1_DONE
    setflag FLAG_HH_SEM2_DONE
    setflag FLAG_HH_SEM3_DONE
    setflag FLAG_HH_SEM4_DONE
    setflag FLAG_HH_SEM5_DONE
    setflag FLAG_HH_SEM6_DONE
    setflag FLAG_HH_SEM7_DONE
    setflag FLAG_HH_SEM8_DONE
    setflag FLAG_HH_SEM9_DONE
    setflag FLAG_HIDE_KLASSENZIMMER_LAST_WIDEFIELD
    lockall
    msgbox HallwayHub_Text_Sem9, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, HallwayHub_Move_Sem9
    waitmovement 0
    playse SE_DOOR
    waitse
    releaseall
    warpsilent MAP_KLASSENZIMMER_LAST, 0, 0, 0
    waitstate
    end


@ =========================
@ Warp-Blocker (für Coord-Events vor den Warp-Kacheln)
@ =========================
HallwayHub_EventScript_WarpBlocked::
    lock
    msgbox HallwayHub_Text_WarpLocked, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, HallwayHub_Move_BumpDown
    waitmovement 0
    release
    end


@ =========================
@ Movements
@ =========================
HallwayHub_Move_Sem1:
    walk_up
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    step_end

HallwayHub_Move_Sem2:
    walk_up
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_up
    walk_up
    walk_up
    step_end

HallwayHub_Move_Sem3:
    walk_up
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_up
    walk_up
    walk_up
    step_end

HallwayHub_Move_Sem4:
    walk_up
    walk_left
    walk_left
    walk_left
    walk_up
    walk_up
    walk_up
    step_end

HallwayHub_Move_Sem5:
    walk_up
    walk_right
    walk_right
    walk_right
    walk_right
    walk_up
    walk_up
    walk_up
    step_end

HallwayHub_Move_Sem6:
    walk_up
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_up
    walk_up
    walk_up
    step_end

HallwayHub_Move_Sem7:
    walk_up
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_up
    walk_up
    walk_up
    step_end

HallwayHub_Move_Sem8:
    walk_up
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    step_end

HallwayHub_Move_Sem9:
    walk_up
    walk_up
    walk_up
    walk_up
    step_end

HallwayHub_Move_BumpDown:
    walk_down
    step_end


@ =========================
@ Texte
@ =========================
HallwayHub_Text_Sem1:
    .string "So this is my new university.\n"
    .string "I'll head over to the room\p"
    .string "they mentioned.$"

HallwayHub_Text_Sem2:
    .string "Second semester, let's go.$"

HallwayHub_Text_Sem3:
    .string "Third semester, let's go.$"

HallwayHub_Text_Sem4:
    .string "Fourth semester, let's go.$"

HallwayHub_Text_Sem5:
    .string "Fifth semester, let's go.$"

HallwayHub_Text_Sem6:
    .string "Sixth semester, let's go.$"

HallwayHub_Text_Sem7:
    .string "Another lecture it is!$"

HallwayHub_Text_Sem8:
    .string "Hopefully, I'll finally get\n"
    .string "my diploma now.$"

HallwayHub_Text_Sem9:
    .string "Huh? Where did that\n"
    .string "come from?$"

HallwayHub_Text_WarpLocked:
    .string "It's not time for this room yet.$"

