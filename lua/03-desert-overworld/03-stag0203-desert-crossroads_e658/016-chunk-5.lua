if be:MATisPlayer() == 1 then
    if g_IFLG04 ~= 1 then
        if g_IFLG00 == 6 then
            be:sd("MODELCTRL", "g_turnstra", 5, "GENERATE", "V<-500,15,-870>/V<0,-90,0>/SQ_POWERON1")
            be:sd("MODELCTRL", "g_turnright", 5, "GENERATE", "V<-500,15,-730>/V<0,-90,0>/SQ_POWERON2")
            be:sd("MODELCTRL", "j_panels0203", 0, "GENERATE", "V<0,0,0>/V<0,0,0>")
            g_IFLG01 = 1
        end
        g_IFLG04 = 1
    else
    end
end
if g_IFLG00 == 6 then
    be:sd("MODELCTRL", "g_turnstra", 5, "SQ_POWEROF")
    be:sd("MODELCTRL", "g_turnright", 5, "SQ_POWEROF")
    be:sd("MODELCTRL", "j_panels0203", 0, "SQ_CLOSE", 10)
    if g_IFLG01 == 1 then
        be:sd("MODELCTRL", "r_trainz02", 0, "SQ_CHANGEI1")
        g_IFLG02 = g_IFLG00
        g_IFLG00 = 3
    else
        be:sd("MODELCTRL", "r_trainz02", 0, "SQ_CHANGEI2")
        g_IFLG02 = g_IFLG00
        g_IFLG00 = 5
    end
end
g_IFLG04 = 0
