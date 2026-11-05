if be:MATisPlayer() == 1 then
    if g_IFLG05 ~= 1 then
        if g_IFLG00 == 7 then
            be:sd("MODELCTRL", "g_turnstra", 6, "GENERATE", "V<-500,15,270>/V<0,-90,0>/SQ_POWERON1")
            be:sd("MODELCTRL", "g_turnleft", 0, "GENERATE", "V<-500,15,130>/V<0,-90,0>/SQ_POWERON2")
            be:sd("MODELCTRL", "j_panels0203", 0, "GENERATE", "V<0,0,0>/V<0,0,0>")
            g_IFLG01 = 1
        end
        g_IFLG05 = 1
    else
    end
end
if g_IFLG00 == 7 then
    be:sd("MODELCTRL", "g_turnstra", 6, "SQ_POWEROF")
    be:sd("MODELCTRL", "g_turnleft", 0, "SQ_POWEROF")
    be:sd("MODELCTRL", "j_panels0203", 0, "SQ_CLOSE", 10)
    if g_IFLG01 == 1 then
        be:sd("MODELCTRL", "r_trainz02", 0, "SQ_CHANGEA1")
        g_IFLG02 = g_IFLG00
        g_IFLG00 = 2
    else
        be:sd("MODELCTRL", "r_trainz02", 0, "SQ_CHANGEA2")
        g_IFLG02 = g_IFLG00
        g_IFLG00 = 1
    end
end
g_IFLG05 = 0
