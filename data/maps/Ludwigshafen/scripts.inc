Ludwigshafen_MapScripts::
    .byte 0


@ Trigger: beim Drauftreten wird das Intro einmalig abgespielt
Ludwigshafen_EventScript_IntroTrigger::
    lockall
    goto_if_set FLAG_LUDWIGSHAFEN_INTRO_DONE, Ludwigshafen_Intro_Done

    msgbox Ludwigshafen_Text_PleaseWait, MSGBOX_DEFAULT
    closemessage

    @ NPCs laufen 6 Tiles nach rechts auf den Spieler zu
    applymovement LOCALID_WANDA,  Ludwigshafen_Movement_ApproachRight6
    applymovement LOCALID_AMANDA, Ludwigshafen_Movement_ApproachRight6
    waitmovement 0

    msgbox Ludwigshafen_Text_WandaAmanda_Intro, MSGBOX_DEFAULT
    closemessage

    @ Beide laufen 23 nach links, Spieler läuft hinterher
    applymovement LOCALID_WANDA,  Ludwigshafen_Movement_WalkLeft23
    applymovement LOCALID_AMANDA, Ludwigshafen_Movement_WalkLeft23

    applymovement LOCALID_PLAYER, Ludwigshafen_Movement_WalkLeft23

    waitmovement 0

    applymovement LOCALID_AMANDA, Ludwigshafen_Movement_FaceRight
    applymovement LOCALID_WANDA,  Ludwigshafen_Movement_FaceRight

    waitmovement 0

    msgbox Ludwigshafen_Text_Both_Glitchy, MSGBOX_DEFAULT

    setflag FLAG_LUDWIGSHAFEN_INTRO_DONE

Ludwigshafen_Movement_FaceRight:
    face_right
    step_end

Ludwigshafen_Intro_Done:
    releaseall
    end


@ Nach dem Intro: beide sagen nur noch "Please hurry!"
Ludwigshafen_EventScript_Wanda_After::
    lock
    faceplayer
    msgbox Ludwigshafen_Text_Both_PleaseHurry, MSGBOX_DEFAULT
    release
    end

Ludwigshafen_EventScript_Amanda_After::
    lock
    faceplayer
    msgbox Ludwigshafen_Text_Both_PleaseHurry, MSGBOX_DEFAULT
    release
    end


@ ----------------
@ Movements
@ ----------------

Ludwigshafen_Movement_ApproachRight6:
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    step_end

Ludwigshafen_Movement_WalkLeft23:
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


@ ----------------
@ Text
@ ----------------

Ludwigshafen_Text_PleaseWait:
    .string "Hey you, please wait!$"

Ludwigshafen_Text_WandaAmanda_Intro:
    .string "WANDA: Quick, you have to help us!\p"
	.string "{PLAYER}: Sure, what's up?\n"
    .string "AMANDA: The doctor is in danger!$"

Ludwigshafen_Text_Both_Glitchy:
    .string "BOTH: Everything is so glitchy,\n"
	.string "hurry up and go inside!$"

Ludwigshafen_Text_Both_PleaseHurry:
    .string "BOTH: Please hurry!$"





@ =========================================================
@ Fake Trade Evo: generisch für alle Trade-Mons
@ =========================================================
Ludwigshafen_EventScript_FakeTradeEvo_HaunterToGengar::
    lock
    faceplayer

    msgbox Ludwigshafen_Text_TradeEvoInvite, MSGBOX_YESNO
    compare VAR_RESULT, NO
    goto_if_eq Ludwigshafen_TradeEvo_End

Ludwigshafen_TradeEvo_SelectLoop:
    msgbox Ludwigshafen_Text_TradeEvoChoose, MSGBOX_DEFAULT
    closemessage

    special ChoosePartyMon
    waitstate

    @ Cancel / invalid
    goto_if_ge VAR_0x8004, PARTY_SIZE, Ludwigshafen_TradeEvo_End

    call Ludwigshafen_TradeEvo_ConfigureSelectedMon
    compare VAR_RESULT, 1
    goto_if_ne Ludwigshafen_TradeEvo_WrongMon

    playse SE_WARP_IN
    playse SE_WARP_OUT
    waitse

    special Special_FakeTradeEvolveSelectedToTarget
    waitstate

    @ 1 = Evolution gestartet
    @ 2 = falsche Species
    @ 3 = Ei
    @ 4 = Everstone blockt
    @ 5 = benötigtes Held-Item fehlt
    compare VAR_RESULT, 1
    goto_if_eq Ludwigshafen_TradeEvo_Success

    compare VAR_RESULT, 3
    goto_if_eq Ludwigshafen_TradeEvo_IsEgg

    compare VAR_RESULT, 4
    goto_if_eq Ludwigshafen_TradeEvo_Everstone

    compare VAR_RESULT, 5
    goto_if_eq Ludwigshafen_TradeEvo_NoItem

    goto Ludwigshafen_TradeEvo_WrongMon

Ludwigshafen_TradeEvo_Success:
    msgbox Ludwigshafen_Text_TradeEvoAfter, MSGBOX_DEFAULT
    goto Ludwigshafen_TradeEvo_End

Ludwigshafen_TradeEvo_WrongMon:
    msgbox Ludwigshafen_Text_TradeEvoWrongMon, MSGBOX_DEFAULT
    goto Ludwigshafen_TradeEvo_SelectLoop

Ludwigshafen_TradeEvo_IsEgg:
    msgbox Ludwigshafen_Text_TradeEvoIsEgg, MSGBOX_DEFAULT
    goto Ludwigshafen_TradeEvo_SelectLoop

Ludwigshafen_TradeEvo_Everstone:
    msgbox Ludwigshafen_Text_TradeEvoEverstone, MSGBOX_DEFAULT
    goto Ludwigshafen_TradeEvo_SelectLoop

Ludwigshafen_TradeEvo_NoItem:
    msgbox Ludwigshafen_Text_TradeEvoNoItem, MSGBOX_DEFAULT
    goto Ludwigshafen_TradeEvo_SelectLoop

Ludwigshafen_TradeEvo_End:
    release
    end


@ =========================================================
@ Konfiguration für gewähltes Party-Pokémon
@ Setzt:
@ VAR_0x8005 = benötigte Species
@ VAR_0x8006 = Ziel-Species
@ VAR_0x8007 = benötigtes Held-Item (ITEM_NONE falls keines)
@ VAR_0x8008 = Everstone ignorieren? (0 nein)
@ VAR_0x8009 = Item verbrauchen? (0 nein)
@ VAR_RESULT = 1 wenn unterstützt, sonst 0
@ =========================================================

Ludwigshafen_TradeEvo_ConfigureSelectedMon:
    specialvar VAR_RESULT, ScriptGetPartyMonSpecies

    compare VAR_RESULT, SPECIES_HAUNTER
    goto_if_eq Ludwigshafen_TradeEvo_Set_Haunter

    compare VAR_RESULT, SPECIES_KADABRA
    goto_if_eq Ludwigshafen_TradeEvo_Set_Kadabra

    compare VAR_RESULT, SPECIES_MACHOKE
    goto_if_eq Ludwigshafen_TradeEvo_Set_Machoke

    compare VAR_RESULT, SPECIES_GRAVELER
    goto_if_eq Ludwigshafen_TradeEvo_Set_Graveler

    compare VAR_RESULT, SPECIES_GRAVELER_ALOLA
    goto_if_eq Ludwigshafen_TradeEvo_Set_GravelerAlola

    compare VAR_RESULT, SPECIES_ONIX
    goto_if_eq Ludwigshafen_TradeEvo_Set_Onix

    compare VAR_RESULT, SPECIES_SCYTHER
    goto_if_eq Ludwigshafen_TradeEvo_Set_Scyther

    compare VAR_RESULT, SPECIES_SEADRA
    goto_if_eq Ludwigshafen_TradeEvo_Set_Seadra

    compare VAR_RESULT, SPECIES_SLOWPOKE
    goto_if_eq Ludwigshafen_TradeEvo_Set_Slowpoke

    compare VAR_RESULT, SPECIES_POLIWHIRL
    goto_if_eq Ludwigshafen_TradeEvo_Set_Poliwhirl

    compare VAR_RESULT, SPECIES_PORYGON
    goto_if_eq Ludwigshafen_TradeEvo_Set_Porygon

    compare VAR_RESULT, SPECIES_PORYGON2
    goto_if_eq Ludwigshafen_TradeEvo_Set_Porygon2

    compare VAR_RESULT, SPECIES_RHYDON
    goto_if_eq Ludwigshafen_TradeEvo_Set_Rhydon

    compare VAR_RESULT, SPECIES_ELECTABUZZ
    goto_if_eq Ludwigshafen_TradeEvo_Set_Electabuzz

    compare VAR_RESULT, SPECIES_MAGMAR
    goto_if_eq Ludwigshafen_TradeEvo_Set_Magmar

    compare VAR_RESULT, SPECIES_CLAMPERL
    goto_if_eq Ludwigshafen_TradeEvo_Set_Clamperl

    compare VAR_RESULT, SPECIES_DUSCLOPS
    goto_if_eq Ludwigshafen_TradeEvo_Set_Dusclops

    compare VAR_RESULT, SPECIES_BOLDORE
    goto_if_eq Ludwigshafen_TradeEvo_Set_Boldore

    compare VAR_RESULT, SPECIES_GURDURR
    goto_if_eq Ludwigshafen_TradeEvo_Set_Gurdurr

    compare VAR_RESULT, SPECIES_KARRABLAST
    goto_if_eq Ludwigshafen_TradeEvo_Set_Karrablast

    compare VAR_RESULT, SPECIES_SHELMET
    goto_if_eq Ludwigshafen_TradeEvo_Set_Shelmet

    compare VAR_RESULT, SPECIES_PHANTUMP
    goto_if_eq Ludwigshafen_TradeEvo_Set_Phantump

    compare VAR_RESULT, SPECIES_SPRITZEE
    goto_if_eq Ludwigshafen_TradeEvo_Set_Spritzee

    compare VAR_RESULT, SPECIES_SWIRLIX
    goto_if_eq Ludwigshafen_TradeEvo_Set_Swirlix

    compare VAR_RESULT, SPECIES_PUMPKABOO
    goto_if_eq Ludwigshafen_TradeEvo_Set_PumpkabooAverage

    compare VAR_RESULT, SPECIES_PUMPKABOO_SMALL
    goto_if_eq Ludwigshafen_TradeEvo_Set_PumpkabooSmall

    compare VAR_RESULT, SPECIES_PUMPKABOO_LARGE
    goto_if_eq Ludwigshafen_TradeEvo_Set_PumpkabooLarge

    compare VAR_RESULT, SPECIES_PUMPKABOO_SUPER
    goto_if_eq Ludwigshafen_TradeEvo_Set_PumpkabooSuper

    setvar VAR_RESULT, 0
    return


Ludwigshafen_TradeEvo_Set_Haunter:
    setvar VAR_0x8005, SPECIES_HAUNTER
    setvar VAR_0x8006, SPECIES_GENGAR
    setvar VAR_0x8007, ITEM_NONE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Kadabra:
    setvar VAR_0x8005, SPECIES_KADABRA
    setvar VAR_0x8006, SPECIES_ALAKAZAM
    setvar VAR_0x8007, ITEM_NONE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Machoke:
    setvar VAR_0x8005, SPECIES_MACHOKE
    setvar VAR_0x8006, SPECIES_MACHAMP
    setvar VAR_0x8007, ITEM_NONE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Graveler:
    setvar VAR_0x8005, SPECIES_GRAVELER
    setvar VAR_0x8006, SPECIES_GOLEM
    setvar VAR_0x8007, ITEM_NONE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_GravelerAlola:
    setvar VAR_0x8005, SPECIES_GRAVELER_ALOLA
    setvar VAR_0x8006, SPECIES_GOLEM_ALOLA
    setvar VAR_0x8007, ITEM_NONE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Onix:
    setvar VAR_0x8005, SPECIES_ONIX
    setvar VAR_0x8006, SPECIES_STEELIX
    setvar VAR_0x8007, ITEM_METAL_COAT
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Scyther:
    setvar VAR_0x8005, SPECIES_SCYTHER
    setvar VAR_0x8006, SPECIES_SCIZOR
    setvar VAR_0x8007, ITEM_METAL_COAT
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Seadra:
    setvar VAR_0x8005, SPECIES_SEADRA
    setvar VAR_0x8006, SPECIES_KINGDRA
    setvar VAR_0x8007, ITEM_DRAGON_SCALE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Slowpoke:
    setvar VAR_0x8005, SPECIES_SLOWPOKE
    setvar VAR_0x8006, SPECIES_SLOWKING
    setvar VAR_0x8007, ITEM_KINGS_ROCK
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Poliwhirl:
    setvar VAR_0x8005, SPECIES_POLIWHIRL
    setvar VAR_0x8006, SPECIES_POLITOED
    setvar VAR_0x8007, ITEM_KINGS_ROCK
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Porygon:
    setvar VAR_0x8005, SPECIES_PORYGON
    setvar VAR_0x8006, SPECIES_PORYGON2
    setvar VAR_0x8007, ITEM_UPGRADE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Porygon2:
    setvar VAR_0x8005, SPECIES_PORYGON2
    setvar VAR_0x8006, SPECIES_PORYGON_Z
    setvar VAR_0x8007, ITEM_DUBIOUS_DISC
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Rhydon:
    setvar VAR_0x8005, SPECIES_RHYDON
    setvar VAR_0x8006, SPECIES_RHYPERIOR
    setvar VAR_0x8007, ITEM_PROTECTOR
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Electabuzz:
    setvar VAR_0x8005, SPECIES_ELECTABUZZ
    setvar VAR_0x8006, SPECIES_ELECTIVIRE
    setvar VAR_0x8007, ITEM_ELECTIRIZER
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Magmar:
    setvar VAR_0x8005, SPECIES_MAGMAR
    setvar VAR_0x8006, SPECIES_MAGMORTAR
    setvar VAR_0x8007, ITEM_MAGMARIZER
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Clamperl:
    msgbox Ludwigshafen_Text_TradeEvoClamperlChoice, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq Ludwigshafen_TradeEvo_Set_ClamperlHuntail

    setvar VAR_0x8005, SPECIES_CLAMPERL
    setvar VAR_0x8006, SPECIES_GOREBYSS
    setvar VAR_0x8007, ITEM_DEEP_SEA_SCALE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_ClamperlHuntail:
    setvar VAR_0x8005, SPECIES_CLAMPERL
    setvar VAR_0x8006, SPECIES_HUNTAIL
    setvar VAR_0x8007, ITEM_DEEP_SEA_TOOTH
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Dusclops:
    setvar VAR_0x8005, SPECIES_DUSCLOPS
    setvar VAR_0x8006, SPECIES_DUSKNOIR
    setvar VAR_0x8007, ITEM_REAPER_CLOTH
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Boldore:
    setvar VAR_0x8005, SPECIES_BOLDORE
    setvar VAR_0x8006, SPECIES_GIGALITH
    setvar VAR_0x8007, ITEM_NONE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Gurdurr:
    setvar VAR_0x8005, SPECIES_GURDURR
    setvar VAR_0x8006, SPECIES_CONKELDURR
    setvar VAR_0x8007, ITEM_NONE
    goto Ludwigshafen_TradeEvo_CommonReturn

@ Partner-Bedingung aus echter Trade-Logik wird hier bewusst ignoriert
Ludwigshafen_TradeEvo_Set_Karrablast:
    setvar VAR_0x8005, SPECIES_KARRABLAST
    setvar VAR_0x8006, SPECIES_ESCAVALIER
    setvar VAR_0x8007, ITEM_NONE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Shelmet:
    setvar VAR_0x8005, SPECIES_SHELMET
    setvar VAR_0x8006, SPECIES_ACCELGOR
    setvar VAR_0x8007, ITEM_NONE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Phantump:
    setvar VAR_0x8005, SPECIES_PHANTUMP
    setvar VAR_0x8006, SPECIES_TREVENANT
    setvar VAR_0x8007, ITEM_NONE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Spritzee:
    setvar VAR_0x8005, SPECIES_SPRITZEE
    setvar VAR_0x8006, SPECIES_AROMATISSE
    setvar VAR_0x8007, ITEM_SACHET
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_Swirlix:
    setvar VAR_0x8005, SPECIES_SWIRLIX
    setvar VAR_0x8006, SPECIES_SLURPUFF
    setvar VAR_0x8007, ITEM_WHIPPED_DREAM
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_PumpkabooAverage:
    setvar VAR_0x8005, SPECIES_PUMPKABOO
    setvar VAR_0x8006, SPECIES_GOURGEIST_AVERAGE
    setvar VAR_0x8007, ITEM_NONE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_PumpkabooSmall:
    setvar VAR_0x8005, SPECIES_PUMPKABOO_SMALL
    setvar VAR_0x8006, SPECIES_GOURGEIST_SMALL
    setvar VAR_0x8007, ITEM_NONE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_PumpkabooLarge:
    setvar VAR_0x8005, SPECIES_PUMPKABOO_LARGE
    setvar VAR_0x8006, SPECIES_GOURGEIST_LARGE
    setvar VAR_0x8007, ITEM_NONE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_Set_PumpkabooSuper:
    setvar VAR_0x8005, SPECIES_PUMPKABOO_SUPER
    setvar VAR_0x8006, SPECIES_GOURGEIST_SUPER
    setvar VAR_0x8007, ITEM_NONE
    goto Ludwigshafen_TradeEvo_CommonReturn

Ludwigshafen_TradeEvo_CommonReturn:
    setvar VAR_0x8008, 0
    setvar VAR_0x8009, 0
    setvar VAR_RESULT, 1
    return


@ =========================================================
@ 2) Geschenk-NPC: Gibt 1x Haunter (einmalig per Flag)
@ =========================================================
Ludwigshafen_EventScript_GiftHaunter::
    lock
    faceplayer

    goto_if_set FLAG_LUDWIGSHAFEN_GOT_HAUNTER_GIFT, Ludwigshafen_GiftHaunter_AlreadyDone

    msgbox Ludwigshafen_Text_GiftHaunterOffer, MSGBOX_YESNO
    compare VAR_RESULT, NO
    goto_if_eq Ludwigshafen_GiftHaunter_End

    msgbox Ludwigshafen_Text_GiftHaunterGive, MSGBOX_DEFAULT
    closemessage

    givemon SPECIES_HAUNTER, 20, ITEM_NONE

    setflag FLAG_LUDWIGSHAFEN_GOT_HAUNTER_GIFT
    msgbox Ludwigshafen_Text_GiftHaunterAfter, MSGBOX_DEFAULT
    goto Ludwigshafen_GiftHaunter_End

Ludwigshafen_GiftHaunter_AlreadyDone:
    msgbox Ludwigshafen_Text_GiftHaunterAlreadyDone, MSGBOX_DEFAULT

Ludwigshafen_GiftHaunter_End:
    release
    end



@ =========================================================
@ Texte
@ =========================================================
Ludwigshafen_Text_TradeEvoInvite:
    .string "ILJA: Hey, we're swapping our POKéMON\n"
    .string "so they can evolve.\p"
    .string "RENE: Then we'll swap them back so \n"
    .string "everyone can keep their own.\p"
    .string "ILJA: Want to join us?$"

Ludwigshafen_Text_TradeEvoChoose:
    .string "Pick the POKéMON you want to evolve.$"

Ludwigshafen_Text_TradeEvoAfter:
    .string "Nice! That trade vibe did the trick!\n"
    .string "Your POKéMON evolved!$"
    
Ludwigshafen_Text_TradeEvoWrongMon:
    .string "That Pokémon doesn't evolve \n"
    .string "through trading.$"

Ludwigshafen_Text_TradeEvoIsEgg:
    .string "That's an Egg. That won't work.$"

Ludwigshafen_Text_TradeEvoEverstone:
    .string "It's holding an Everstone.\n"
    .string "That blocks the evolution!$"

Ludwigshafen_Text_TradeEvoNoItem:
    .string "It needs to hold a specific item\n"
    .string "for this evolution.$"

Ludwigshafen_Text_TradeEvoClamperlChoice:
    .string "Should CLAMPERL evolve into\n"
    .string "HUNTAIL?\p"
    .string "Choose NO for GOREBYSS.$"





Ludwigshafen_Text_GiftHaunterOffer:
    .string "Hey! I found a spooky Pokémon.\n"
    .string "Do you want this HAUNTER?$"

Ludwigshafen_Text_GiftHaunterGive:
    .string "Alright! Take good care of it.$"

Ludwigshafen_Text_GiftHaunterAfter:
    .string "If you ever trade it, something\n"
    .string "interesting might happen...$"

Ludwigshafen_Text_GiftHaunterPartyFull:
    .string "Your party is full.\n"
    .string "Make room first!$"

Ludwigshafen_Text_GiftHaunterAlreadyDone:
    .string "How's that HAUNTER doing?$"






@ =========================================================
@ Debug Haunter flag


Ludwigshafen_EventScript_DebugGiftFlagToggle::
    lock
    faceplayer

    checkflag FLAG_LUDWIGSHAFEN_GOT_HAUNTER_GIFT
    goto_if_eq VAR_RESULT, TRUE, Ludwigshafen_Debug_FlagIsSet

Ludwigshafen_Debug_FlagIsNotSet:
    msgbox Ludwigshafen_Text_Debug_NotSet, MSGBOX_DEFAULT
    setflag FLAG_LUDWIGSHAFEN_GOT_HAUNTER_GIFT
    release
    end

Ludwigshafen_Debug_FlagIsSet:
    msgbox Ludwigshafen_Text_Debug_IsSet, MSGBOX_DEFAULT
    clearflag FLAG_LUDWIGSHAFEN_GOT_HAUNTER_GIFT
    release
    end

Ludwigshafen_Text_Debug_NotSet:
    .string "DEBUG: Flag ist NICHT gesetzt.\nIch setze sie jetzt.$"
Ludwigshafen_Text_Debug_IsSet:
    .string "DEBUG: Flag ist gesetzt.\nIch loesche sie jetzt.$"


@ =========================================================
@ Schilder
@ =========================================================


Ludwigshafen_EventScript_ChallengeHouseSign::
	msgbox Ludwigshafen_Text_ChallengeHouseSign, MSGBOX_SIGN
	end

Ludwigshafen_Text_ChallengeHouseSign::
	.string "Challenge House$"



Ludwigshafen_EventScript_FerrySign::
	msgbox Ludwigshafen_Text_FerrySign, MSGBOX_SIGN
	end

Ludwigshafen_Text_FerrySign::
	.string "Ferry$"



Ludwigshafen_EventScript_StudiesSign::
	msgbox Ludwigshafen_Text_StudiesSign, MSGBOX_SIGN
	end

Ludwigshafen_Text_StudiesSign::
	.string "Saved Studies$"


Ludwigshafen_EventScript_NameRaterSign::
	msgbox Ludwigshafen_Text_NameRaterSign, MSGBOX_SIGN
	end

Ludwigshafen_Text_NameRaterSign::
	.string "Name Rater$"


Ludwigshafen_EventScript_FanclubSign::
	msgbox Ludwigshafen_Text_FanclubSign, MSGBOX_SIGN
	end

Ludwigshafen_Text_FanclubSign::
	.string "LUDWIGSHAFEN POKÉMON Fan Club$"


Ludwigshafen_EventScript_LUSign::
	msgbox Ludwigshafen_Text_LUSign, MSGBOX_SIGN
	end

Ludwigshafen_Text_LUSign::
	.string "LUDWIGSHAFEN. True LU!$"

Ludwigshafen_EventScript_MarketSign::
	msgbox Ludwigshafen_Text_MarketSign, MSGBOX_SIGN
	end

Ludwigshafen_Text_MarketSign::
	.string "Weekly Farmer's Market$"

Ludwigshafen_EventScript_WharfSign::
	msgbox Ludwigshafen_Text_WharfSign, MSGBOX_SIGN
	end

Ludwigshafen_Text_WharfSign::
	.string "Wharf$"

Ludwigshafen_EventScript_ClosedSign::
	msgbox Ludwigshafen_Text_ClosedSign, MSGBOX_SIGN
	end

Ludwigshafen_Text_ClosedSign::
	.string "Route Closed$"

