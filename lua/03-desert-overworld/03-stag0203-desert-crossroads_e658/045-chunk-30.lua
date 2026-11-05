if be:MATisPlayer() == 1 then
    if g_IFLG05 ~= 1 then
        be:sd("MODELCTRL", "g_gatesign", 0, "SQ_POWERON")
        g_IFLG01 = 2
        g_IFLG05 = 1
    else
    end
end
if g_IFLG00 == 20 then
    if g_IFLG01 == 1 then
        be:sd("MODELCTRL", "r_trainz02", 0, "SQ_CHANGEI1")
        g_IFLG02 = g_IFLG00
        g_IFLG00 = 21
    else
        be:sd("MODELCTRL", "r_trainz02", 0, "SQ_CHANGEI2")
        g_IFLG02 = g_IFLG00
        g_IFLG00 = 10
    end
    be:sd("MODELCTRL", "g_gatesign", 0, "SQ_POWEROF")
end
g_IFLG05 = 0
