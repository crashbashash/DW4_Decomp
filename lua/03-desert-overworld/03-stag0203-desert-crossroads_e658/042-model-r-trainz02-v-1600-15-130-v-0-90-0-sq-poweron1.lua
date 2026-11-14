if be:MATisPlayer() == 1 then
    if g_IFLG03 ~= 1 then
        if g_IFLG00 == 3 then
            be:sd("MODELCTRL", "g_turnstra", 2, "GENERATE", "V<1600,15,130>/V<0,-90,0>/SQ_POWERON1")
            be:sd("MODELCTRL", "g_turnright", 2, "GENERATE", "V<1600,15,270>/V<0,-90,0>/SQ_POWERON2")
            be:sd("MODELCTRL", "j_panels0203", 0, "GENERATE", "V<0,0,0>/V<0,0,0>")
            g_IFLG01 = 1
        end
        g_IFLG03 = 1
    end
else
    if g_IFLG00 == 3 then
        be:sd("MODELCTRL", "g_turnstra", 2, "SQ_POWEROF")
        be:sd("MODELCTRL", "g_turnright", 2, "SQ_POWEROF")
        be:sd("MODELCTRL", "j_panels0203", 0, "SQ_CLOSE", 10)
        if g_IFLG01 == 1 then
            if g_IFLG02 == 2 then
                be:sd("MODELCTRL", "r_trainz02", 0, "SQ_CHANGEB1")
            elseif g_IFLG02 == 6 then
                be:sd("MODELCTRL", "r_trainz02", 0, "SQ_CHANGEF1")
            end
            g_IFLG02 = g_IFLG00
            g_IFLG00 = 10
        else
            if g_IFLG02 == 2 then
                be:sd("MODELCTRL", "r_trainz02", 0, "SQ_CHANGEB2")
            elseif g_IFLG02 == 6 then
                be:sd("MODELCTRL", "r_trainz02", 0, "SQ_CHANGEF2")
            end
            g_IFLG02 = g_IFLG00
            g_IFLG00 = 8
        end
    end
    g_IFLG03 = 0
end
