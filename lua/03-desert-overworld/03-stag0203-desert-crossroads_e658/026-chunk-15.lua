if be:MATisPlayer() == 1 then
    if g_matf05on ~= 1 then
        if g_IFLG00 == 1 then
            if be:MDLisLive("g_cannonz06", 10) ~= 1 then
                be:sd("MODELCTRL", "g_cannonz06", 10, "GENERATE", "V<1300,15,-300>/V<0,30,0>/SQ_POWERON")
                be:sd("MODELCTRL", "g_cannonz06", 11, "GENERATE", "V<1500,15,-300>/V<0,-30,0>/SQ_POWERON")
            else
            end
        end
        if g_IFLG00 == 3 and be:MDLisLive("g_cannonz06", 10) ~= 1 then
            be:sd("MODELCTRL", "g_cannonz06", 10, "GENERATE", "V<1300,15,-300>/V<0,150,0>/SQ_POWERON")
            be:sd("MODELCTRL", "g_cannonz06", 11, "GENERATE", "V<1500,15,-300>/V<0,-150,0>/SQ_POWERON")
        end
        g_matf05on = 1
    else
    end
end
g_matf05on = 0
