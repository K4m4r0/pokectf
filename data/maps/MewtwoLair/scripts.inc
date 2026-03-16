MewtwoLair_MapScripts::
    .byte 0

    .equ MEWTWO_LEVEL, 40

MewtwoLair_EventScript_Mewtwo::
    lockall
    faceplayer

    goto_if_set FLAG_MEWTWO_LAIR_MEWTWO_GONE, MewtwoLair_End

    msgbox MewtwoLair_Text_MewtwoIntro1, MSGBOX_DEFAULT
    msgbox MewtwoLair_Text_MewtwoIntro2, MSGBOX_DEFAULT
    msgbox MewtwoLair_Text_MewtwoIntro3, MSGBOX_DEFAULT
    closemessage

    setflag FLAG_MEWTWO_LAIR_SPECIAL_BATTLE
    setwildbattle SPECIES_MEWTWO, MEWTWO_LEVEL, ITEM_NONE
    specialvar VAR_RESULT, BattleSetup_StartLegendaryBattle
    waitstate

    compare VAR_RESULT, 7
    goto_if_eq MewtwoLair_Caught

    compare VAR_RESULT, 1
    goto_if_eq MewtwoLair_Defeated

    clearflag FLAG_MEWTWO_LAIR_SPECIAL_BATTLE
    releaseall
    end

MewtwoLair_Caught:
    clearflag FLAG_MEWTWO_LAIR_SPECIAL_BATTLE
    msgbox MewtwoLair_Text_MewtwoCaught, MSGBOX_DEFAULT
    setflag FLAG_MEWTWO_LAIR_MEWTWO_GONE
    removeobject LOCALID_MEWTWO
    releaseall
    end

MewtwoLair_Defeated:
    clearflag FLAG_MEWTWO_LAIR_SPECIAL_BATTLE
    setflag FLAG_MEWTWO_LAIR_MEWTWO_GONE
    removeobject LOCALID_MEWTWO
    releaseall
    end

MewtwoLair_End:
    releaseall
    end

MewtwoLair_Text_MewtwoIntro1:
    .string "MEWTWO: I was created to serve\n"
    .string "others... to be used as a weapon.\p"
    .string "TEAM ROCKET sought to command me,\n"
    .string "but I broke free.$"

MewtwoLair_Text_MewtwoIntro2:
    .string "MEWTWO: Since then I have hidden\n"
    .string "myself, far from their reach.\p"
    .string "I have heard of your exploits,\n"
    .string "{PLAYER}.$"

MewtwoLair_Text_MewtwoIntro3:
    .string "MEWTWO: You may be a worthy opponent.\p"
    .string "But first... you must prove it.$"

MewtwoLair_Text_MewtwoCaught:
    .string "MEWTWO: Alright, I'll come with you\n"
    .string "...for now...$"

