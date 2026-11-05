if be:MATisAllPlayer() == 1 then
    if g_matf04on ~= 1 and g_IFLG00 == 10 and be:MDLisLive("g_cannonz06", 8) ~= 1 then
        be:sd("MODELCTRL", "g_cannonz06", 8, "GENERATE", "V<2500,15,100>/V<0,-60,0>/SQ_POWERON")
        be:sd("MODELCTRL", "g_cannonz06", 9, "GENERATE", "V<2500,15,300>/V<0,-120,0>/SQ_POWERON")
    end
    g_matf04on = 1
else
    g_matf04on = 0
end
