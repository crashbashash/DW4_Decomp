if be:MATisPlayer() == 1 then
    if g_IFLG05 ~= 1 then
        be:sd("MODELCTRL", "g_gatesign", 1, "SQ_POWERON")
        g_IFLG01 = 2
        g_IFLG05 = 1
    end
else
    if g_IFLG00 == 21 then
        if g_IFLG01 == 1 then
            be:sd("MODELCTRL", "r_trainz02", 0, "SQ_CHANGEJ1")
            g_IFLG02 = g_IFLG00
            g_IFLG00 = 22
        else
            be:sd("MODELCTRL", "r_trainz02", 0, "SQ_CHANGEJ2")
            g_IFLG02 = g_IFLG00
            g_IFLG00 = 10
        end
        be:sd("MODELCTRL", "g_gatesign", 1, "SQ_POWEROF")
    end
    g_IFLG05 = 0
end
