if be:MATisAllPlayer() == 1 and g_IFLG00 == 10 and be:DMgetCount() == 0 then
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:DMsetSD("MODELCTRL", "i_stpnl00", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_stpnl01", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_stpnl02", -1, "SQ_CLOSEWN")
    be:DMsetSD("MODELCTRL", "i_stpnl03", -1, "SQ_CLOSEWN")
    be:DMsetSD("MODELCTRL", "i_stpnl04", -1, "SQ_CLOSEWN")
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT60")
    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<4>", 100)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stag0201", 100)
    be:DMrun()
elseif be:MATisAllPlayer() == 1 and g_IFLG00 ~= 1 then
    g_IFLG00 = 1
    g_IFLG01 = 1
    g_IFLG02 = 0
end
