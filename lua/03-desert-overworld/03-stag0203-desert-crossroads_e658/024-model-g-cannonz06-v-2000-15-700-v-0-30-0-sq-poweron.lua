if be:MATisPlayer() == 1 then
    if g_matf03on ~= 1 then
        if g_IFLG00 == 4 then
            if be:MDLisLive("g_cannonz06", 6) ~= 1 then
                be:sd("MODELCTRL", "g_cannonz06", 6, "GENERATE", "V<2000,15,700>/V<0,30,0>/SQ_POWERON")
                be:sd("MODELCTRL", "g_cannonz06", 7, "GENERATE", "V<2200,15,700>/V<0,-30,0>/SQ_POWERON")
            end
        elseif g_IFLG00 == 8 and be:MDLisLive("g_cannonz06", 6) ~= 1 then
            be:sd("MODELCTRL", "g_cannonz06", 6, "GENERATE", "V<2000,15,700>/V<0,150,0>/SQ_POWERON")
            be:sd("MODELCTRL", "g_cannonz06", 7, "GENERATE", "V<2200,15,700>/V<0,-150,0>/SQ_POWERON")
        end
        g_matf03on = 1
    end
else
    g_matf03on = 0
end
