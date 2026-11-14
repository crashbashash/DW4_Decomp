if be:FLGisOn(424) == 0 then
    g_StChangeKind = "trans"
    if be:MATisAllPlayer() == 1 then
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
        be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
        be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
        mswk70028 = "STCHGFONT00/font00/I<59>"
        funcStageChange("stagML02", 0, mswk70028, 0)
    end
else
end
