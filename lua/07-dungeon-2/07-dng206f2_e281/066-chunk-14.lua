if be:MATisPlayer() == 1 then
    if g_dmovescaffold ~= 1 then
        be:sd("MODELCTRL", "g_dmovescaffold", 0, "SQ_SWON")
        be:sd("MODELCTRL", "g_dmovescaffold", 1, "SQ_SWON")
        be:sd("MODELCTRL", "g_dmovescaffold", 2, "SQ_SWON")
        g_dmovescaffold = 1
    else
    end
end
be:sd("MODELCTRL", "g_dmovescaffold", 0, "SQ_WAIT")
be:sd("MODELCTRL", "g_dmovescaffold", 1, "SQ_WAIT")
be:sd("MODELCTRL", "g_dmovescaffold", 2, "SQ_WAIT")
g_dmovescaffold = 0
