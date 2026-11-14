if be:MATisPlayer() == 1 then
    if g_matf00on ~= 1 then
        if g_IFLG00 == 4 and g_IFLG02 == 1 then
            if be:MDLisLive("g_cannonz06", 0) ~= 1 then
                be:sd("MODELCTRL", "g_cannonz06", 0, "GENERATE", "V<-300,15,500>/V<0,-60,0>/SQ_POWERON")
                be:sd("MODELCTRL", "g_cannonz06", 1, "GENERATE", "V<-300,15,700>/V<0,-120,0>/SQ_POWERON")
            end
        elseif g_IFLG00 == 5 and be:MDLisLive("g_cannonz06", 0) ~= 1 then
            be:sd("MODELCTRL", "g_cannonz06", 0, "GENERATE", "V<-300,15,500>/V<0,60,0>/SQ_POWERON")
            be:sd("MODELCTRL", "g_cannonz06", 1, "GENERATE", "V<-300,15,700>/V<0,120,0>/SQ_POWERON")
        end
        g_matf00on = 1
    end
else
    g_matf00on = 0
end
