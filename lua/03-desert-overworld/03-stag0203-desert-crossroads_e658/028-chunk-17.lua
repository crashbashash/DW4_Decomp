if be:MATisPlayer() == 1 then
    if g_matf07on ~= 1 then
        if g_IFLG00 == 3 then
            if be:MDLisLive("g_cannonz06", 14) ~= 1 then
                be:sd("MODELCTRL", "g_cannonz06", 14, "GENERATE", "V<500,15,-700>/V<0,-120,0>/SQ_POWERON")
                be:sd("MODELCTRL", "g_cannonz06", 15, "GENERATE", "V<500,15,-900>/V<0,-60,0>/SQ_POWERON")
            else
            end
        end
        if g_IFLG00 == 1 and be:MDLisLive("g_cannonz06", 14) ~= 1 then
            be:sd("MODELCTRL", "g_cannonz06", 14, "GENERATE", "V<500,15,-700>/V<0,120,0>/SQ_POWERON")
            be:sd("MODELCTRL", "g_cannonz06", 15, "GENERATE", "V<500,15,-900>/V<0,60,0>/SQ_POWERON")
        end
        g_matf07on = 1
    else
    end
end
g_matf07on = 0
