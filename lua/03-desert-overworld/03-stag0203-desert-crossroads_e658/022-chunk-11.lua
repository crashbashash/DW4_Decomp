if be:MATisPlayer() == 1 then
    if g_matf01on ~= 1 then
        if g_IFLG00 == 4 and g_IFLG02 ~= 1 and be:MDLisLive("g_cannonz06", 2) == 1 then
            be:sd("MODELCTRL", "g_cannonz06", 2, "GENERATE", "V<700,15,500>/V<0,-60,0>/SQ_POWERON")
            be:sd("MODELCTRL", "g_cannonz06", 3, "GENERATE", "V<700,15,700>/V<0,-120,0>/SQ_POWERON")
        end
        g_matf01on = 1
    else
    end
end
g_matf01on = 0
