g_StChangeKind = "trans"
if be:MATisAllPlayer() == 1 and be:DMgetCount() == 0 then
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
    be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
    mswk70027 = "STCHGFONT00/font00/I<321>"
    funcStageChange("stagML11", 0, mswk70027, 0)
else
end
