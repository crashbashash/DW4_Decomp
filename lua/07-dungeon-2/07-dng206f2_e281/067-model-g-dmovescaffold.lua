if be:MATisPlayer() == 1 then
    if g_dmovescaffold ~= 1 then
        be:sd("MODELCTRL", "g_dmovescaffold", 3, "SQ_SWON")
        be:sd("MODELCTRL", "g_dmovescaffold", 4, "SQ_SWON")
        be:sd("MODELCTRL", "g_dmovescaffold", 5, "SQ_SWON")
        g_dmovescaffold = 1
    end
else
    be:sd("MODELCTRL", "g_dmovescaffold", 3, "SQ_WAIT")
    be:sd("MODELCTRL", "g_dmovescaffold", 4, "SQ_WAIT")
    be:sd("MODELCTRL", "g_dmovescaffold", 5, "SQ_WAIT")
    g_dmovescaffold = 0
end
