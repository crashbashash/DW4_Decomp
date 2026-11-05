if be:MATisPlayer() == 1 then
    if g_matf08on ~= 1 then
        if g_IFLG00 == 20 and be:MDLisLive("g_cannonz06", 16) ~= 1 then
            be:sd("MODELCTRL", "g_cannonz06", 16, "GENERATE", "V<-1400,15,-1300>/V<0,30,0>/SQ_POWERON")
            be:sd("MODELCTRL", "g_cannonz06", 17, "GENERATE", "V<-1200,15,-1300>/V<0,-30,0>/SQ_POWERON")
        end
        g_matf08on = 1
    else
    end
end
g_matf08on = 0
