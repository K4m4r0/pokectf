FinaleFarmer_MapScripts::
	.byte 0

FinaleFarmer_EventScript_PhillipBoss::
    lockall
    faceplayer
    goto_if_set FLAG_BADGE08_GET, FinaleFarmer_AfterScript

    msgbox FinaleFarmer_Text_Dots, MSGBOX_DEFAULT
    closemessage

    turnobject LOCALID_FARMER_FINALE, DIR_SOUTH

    call FinaleFarmer_CheckPartyForI3CLine
    compare VAR_RESULT, 1
    goto_if_eq FinaleFarmer_Intro_Gengar

FinaleFarmer_Intro_Normal:
    msgbox FinaleFarmer_Text_Intro, MSGBOX_DEFAULT
    goto FinaleFarmer_StartBattle

FinaleFarmer_Intro_Gengar:
    msgbox FinaleFarmer_Text_Intro_Gengar, MSGBOX_DEFAULT
    goto FinaleFarmer_StartBattle

FinaleFarmer_StartBattle:
    closemessage
    setvar VAR_LAST_TALKED, LOCALID_FARMER_FINALE
    trainerbattle TRAINER_BATTLE_SINGLE, LOCALID_FARMER_FINALE, TRAINER_PHILLIP, FinaleFarmer_Text_Intro, FinaleFarmer_Text_Lose, FinaleFarmer_AfterBattle, 0, 0, 0, 0, 0, FinaleFarmer_Text_AfterBattle, FinaleFarmer_Text_CannotBattle, 0, 1, 0, 0
    end

FinaleFarmer_AfterScript:
    lockall
    faceplayer

    goto_if_unset FLAG_GOT_DIVE_TOOL_FROM_PHILLIP, FinaleFarmer_GiveDiveToolAfterBattle

    msgbox FinaleFarmer_Text_After, MSGBOX_DEFAULT
    releaseall
    end

@ =========================================================
@ After battle (player won)
@ =========================================================
FinaleFarmer_AfterBattle:
    lockall
    faceplayer
    setflag FLAG_BADGE08_GET

    msgbox FinaleFarmer_Text_VictorySpeech, MSGBOX_DEFAULT
    closemessage

    msgbox FinaleFarmer_Text_BadgeReceived, MSGBOX_DEFAULT
    closemessage

FinaleFarmer_GiveDiveToolAfterBattle:
    msgbox FinaleFarmer_Text_DiveToolIntro, MSGBOX_DEFAULT
    giveitem ITEM_DIVE_TOOL, 1
    compare VAR_RESULT, FALSE
    goto_if_eq FinaleFarmer_DiveToolBagFull

    setflag FLAG_GOT_DIVE_TOOL_FROM_PHILLIP
    releaseall
    end

FinaleFarmer_DiveToolBagFull:
    msgbox FinaleFarmer_Text_DiveToolBagFull, MSGBOX_DEFAULT
    releaseall
    end


@ =========================================================
@ Party Check Helper (STUB)
@ =========================================================

FinaleFarmer_CheckPartyForI3CLine:
    setvar VAR_RESULT, 0

    setvar VAR_0x8004, SPECIES_I3C_AND
    specialvar VAR_0x8005, Special_PartyContainsSpecies
    compare VAR_0x8005, 1
    goto_if_eq .found

    setvar VAR_0x8004, SPECIES_I3C_NAND
    specialvar VAR_0x8005, Special_PartyContainsSpecies
    compare VAR_0x8005, 1
    goto_if_eq .found


    return
.found:
    setvar VAR_RESULT, 1
    return


@ =========================================================
@ Text
@ =========================================================

FinaleFarmer_Text_Dots:
    .string "...$"

FinaleFarmer_Text_Intro:
    .string "PROF. FARMER: You made it.\n"
    .string "Not by luck, by method.\p"
    .string "By curiosity sharpened into skill.\n"
    .string "This is the final lab.\p"
    .string "The final firewall.\n"
    .string "The last system to breach.\p"
    .string "In Computer Science, we don't\n"
    .string "fear complexity, we map it.\p"
    .string "In Cyber Security, we don't\n"
    .string "wait for threats, we anticipate.\p"
    .string "Show me your discipline.\n"
    .string "Show me your craft.\p"
    .string "Show me your proof.$"

FinaleFarmer_Text_Intro_Gengar:
    .string "PROF. FARMER: ...\p"
    .string "That presence in your team...\n"
    .string "A symbol with teeth.\p"
    .string "A reminder that silly vectors\n"
    .string "still strike hardest.\p"
    .string "Good.\n"
    .string "Bring it.\p"
    .string "Let's see if your defenses hold.$"

FinaleFarmer_Text_Lose:
    .string "PROF. FARMER: A system can be restarted.\n"
    .string "A mind can be rebuilt.\p"
    .string "Return when you're ready.$"

FinaleFarmer_Text_AfterBattle:
    .string "PROF. FARMER: Impressive.\n"
    .string "You didn't just win,\p"
    .string "you validated your approach.$"

FinaleFarmer_Text_VictorySpeech:
    .string "PROF. FARMER: That's it.\n"
    .string "No shortcuts.\p"
    .string "No exploits without ethics.\p"
    .string "You demonstrated analysis,\n"
    .string "resilience, and intent.\p"
    .string "From theory to practice.\n"
    .string "From noise to signal.\p"
    .string "From student to specialist.$"

FinaleFarmer_Text_BadgeReceived:
    .string "PROF. FARMER: You received the\n"
    .string "DIGITAL TECHNOLOGY BADGE!\p"
    .string "This badge marks the completion\n"
    .string "of the program.\p"
    .string "Your final credential:\n"
    .string "earned, not given.$"

FinaleFarmer_Text_After:
    .string "PROF. FARMER: You've earned it.\n"
    .string "Carry that badge like a key\p"
    .string "and like a responsibility.$"

FinaleFarmer_Text_CannotBattle:
    .string "PROF. FARMER: You have no usable Pokemon.$"

FinaleFarmer_Text_DiveToolIntro:
    .string "PROF. FARMER: You have found all the flags\n"
    .string "and successfully completed your studies.\p"
    .string "You can now explore the rest of the\n"
    .string "world. This might help you:$"

FinaleFarmer_Text_DiveToolBagFull:
    .string "PROF. FARMER: Your BAG is full.\n"
    .string "Come back after making space.$"


