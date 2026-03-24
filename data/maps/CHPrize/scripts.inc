CHPrize_MapScripts::
    .byte 0


@ =========================================================
@ Prize NPC
@ =========================================================
CHPrize_EventScript_PrizeMaster::
    lock
    faceplayer

    goto_if_set FLAG_CH_PRIZE_RECEIVED, CHPrize_EventScript_PrizeMaster_After

    msgbox CHPrize_Text_PrizeIntro, MSGBOX_DEFAULT
    giveitem ITEM_POKE_FLUTE, 1
    compare VAR_RESULT, FALSE
    goto_if_eq CHPrize_EventScript_PrizeMaster_BagFull

    setflag FLAG_CH_PRIZE_RECEIVED
    msgbox CHPrize_Text_PrizeReceived, MSGBOX_DEFAULT
    release
    end

CHPrize_EventScript_PrizeMaster_BagFull::
    msgbox CHPrize_Text_BagFull, MSGBOX_DEFAULT
    release
    end

CHPrize_EventScript_PrizeMaster_After::
    msgbox CHPrize_Text_After, MSGBOX_DEFAULT
    release
    end


@ =========================================================
@ Text
@ =========================================================
CHPrize_Text_PrizeIntro:
    .string "VALERIA: Congratulations, challenger!\p"
    .string "You mastered every room of the\n"
    .string "Challenge House and proved your worth.\p"
    .string "Please accept this prize: the\n"
    .string "POKé FLUTE.$"

CHPrize_Text_PrizeReceived:
    .string "VALERIA: Use it well.\p"
    .string "A true champion always knows when\n"
    .string "to awaken what others overlook.$"

CHPrize_Text_BagFull:
    .string "Your BAG is full.$"

CHPrize_Text_After:
    .string "VALERIA: Once again, congratulations.\p"
    .string "The Challenge House remembers its\n"
    .string "champions.$"

