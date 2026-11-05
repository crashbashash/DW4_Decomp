mswk70000 = "STCHGFONT01/font01/I<54>"
mswk70010 = "STCHGFONT01/font02/I<55>"
mswk70016 = "STCHGFONT01/font03/I<56>"
mswk70021 = "STCHGFONT01/font04/I<57>"
mswk70057 = "STCHGFONT01/font01/I<58>"
if be:FLGisOn(2) == 1 and be:FLGisOn(409) == 0 then
    if be:MATisAllPlayer() == 1 then
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
        be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
        be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
        if be:FLGisOn(503) == 0 then
            local_0("stag0001", 0, mswk70000)
        else
            local_0("stag0101", 0, mswk70000)
        end
        be:DMrun()
    else
    end
end
if be:FLGisOn(4) == 1 and be:FLGisOn(409) == 0 then
    if be:MATisAllPlayer() == 1 then
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
        be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
        be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
        local_0("stag0101", 0, mswk70000, "stag0201", 0, mswk70010)
        be:DMrun()
    else
    end
end
if be:FLGisOn(5) == 1 and be:FLGisOn(409) == 0 then
    if be:MATisAllPlayer() == 1 then
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
        be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
        be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
        local_0("stag0101", 0, mswk70000, "stag0201", 0, mswk70010, "stag0301", 0, mswk70016)
        be:DMrun()
    else
    end
end
if be:FLGisOn(6) == 1 and be:FLGisOn(409) == 0 then
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
    be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
    if be:MATisAllPlayer() == 1 then
        local_0("stag0101", 0, mswk70000, "stag0201", 0, mswk70010, "stag0301", 0, mswk70016, "stag0401", 0, mswk70021)
        be:DMrun()
    else
    end
end
if be:FLGisOn(86) == 1 and be:FLGisOn(409) == 0 then
    if be:MATisAllPlayer() == 1 then
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
        be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
        be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
        local_0("stag0101", 0, mswk70000, "stag0201", 0, mswk70010, "stag0301", 0, mswk70016, "stag0401", 0, mswk70021)
        be:DMrun()
    else
    end
end
if be:FLGisOn(409) == 1 and be:MATisAllPlayer() == 1 then
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font00/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font01/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font02/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font03/CLR", 5)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "POINTFONT00/font04/CLR", 5)
    be:DMsetSD("MODELCTRL", "i_stpnl06", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_pointcur", -1, "SQ_CLOSE")
    local_0("stag0401", 3, mswk70057)
    be:DMrun()
end
