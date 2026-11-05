if be:MATisPlayer() == 1 then
    if g_matf02on ~= 1 then
        if g_IFLG00 == 4 then
            if be:MDLisLive("g_cannonz06", 4) ~= 1 then
                be:sd("MODELCTRL", "g_cannonz06", 4, "GENERATE", "V<1600,15,1300>/V<0,-60,0>/SQ_POWERON")
                be:sd("MODELCTRL", "g_cannonz06", 5, "GENERATE", "V<1600,15,1500>/V<0,-120,0>/SQ_POWERON")
            else
            end
        end
        if g_IFLG00 == 8 and be:MDLisLive("g_cannonz06", 4) ~= 1 then
            be:sd("MODELCTRL", "g_cannonz06", 4, "GENERATE", "V<1600,15,1300>/V<0,60,0>/SQ_POWERON")
            be:sd("MODELCTRL", "g_cannonz06", 5, "GENERATE", "V<1600,15,1500>/V<0,120,0>/SQ_POWERON")
        end
        g_matf02on = 1
    else
    end
end
g_matf02on = 0
