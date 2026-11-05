if be:MATisPlayer() == 1 then
    if g_IFLG05 ~= 1 then
        if g_IFLG00 == 8 then
            be:sd("MODELCTRL", "g_turnstra", 7, "GENERATE", "V<970,15,1100>/V<0,0,0>/SQ_POWERON1")
            be:sd("MODELCTRL", "g_turnleft", 1, "GENERATE", "V<830,15,1100>/V<0,0,0>/SQ_POWERON2")
            be:sd("MODELCTRL", "j_panels0203", 0, "GENERATE", "V<0,0,0>/V<0,0,0>")
            g_IFLG01 = 1
        end
        g_IFLG05 = 1
    else
    end
end
if g_IFLG00 == 8 then
    be:sd("MODELCTRL", "g_turnstra", 7, "SQ_POWEROF")
    be:sd("MODELCTRL", "g_turnleft", 1, "SQ_POWEROF")
    be:sd("MODELCTRL", "j_panels0203", 0, "SQ_CLOSE", 10)
    g_IFLG02 = g_IFLG00
    if g_IFLG01 == 1 then
        be:sd("MODELCTRL", "r_trainz02", 0, "SQ_CHANGEC1")
        g_IFLG00 = 5
    else
        be:sd("MODELCTRL", "r_trainz02", 0, "SQ_CHANGEC2")
        g_IFLG00 = 5
    end
end
g_IFLG05 = 0
