if be:MATisPlayer() == 1 and be:DMgetCount() == 0 and be:MDLisLive("i_fadewn01", 0) == 0 then
    be:sd("MODELCTRL", nil, -1, "OFCTRL")
    be:sd("STAGECTL", nil, -1, "PADINPUT", "DISABLE")
    be:sd("NDMWPANEL", nil, -1, "NOHEALING", "I<0>")
    be:sd("NDMWPANEL", nil, -1, "NOGATEDISK", "I<0>")
    be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE")
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLOUT60", 60)
    be:DMsetSD("PLAYER", nil, -1, "SQ_ENJOY")
    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 130)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stag0104", 130)
    be:DMrun()
else
end
