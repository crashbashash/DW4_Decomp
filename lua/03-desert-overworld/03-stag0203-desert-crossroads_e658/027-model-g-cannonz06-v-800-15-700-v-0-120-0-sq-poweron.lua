if be:MATisPlayer() == 1 then
    if g_matf06on ~= 1 then
        if g_IFLG00 == 3 then
            if be:MDLisLive("g_cannonz06", 12) ~= 1 then
                be:sd("MODELCTRL", "g_cannonz06", 12, "GENERATE", "V<800,15,-700>/V<0,-120,0>/SQ_POWERON")
                be:sd("MODELCTRL", "g_cannonz06", 13, "GENERATE", "V<800,15,-900>/V<0,-60,0>/SQ_POWERON")
            end
        elseif g_IFLG00 == 1 and be:MDLisLive("g_cannonz06", 12) ~= 1 then
            be:sd("MODELCTRL", "g_cannonz06", 12, "GENERATE", "V<800,15,-700>/V<0,120,0>/SQ_POWERON")
            be:sd("MODELCTRL", "g_cannonz06", 13, "GENERATE", "V<800,15,-900>/V<0,60,0>/SQ_POWERON")
        end
        g_matf06on = 1
    end
else
    g_matf06on = 0
end
