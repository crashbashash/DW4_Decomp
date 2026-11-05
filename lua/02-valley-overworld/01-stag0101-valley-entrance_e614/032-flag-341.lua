if be:MATisPlayer() == 1 and be:FLGisOn(341) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 4, "SQ_POWERON")
    be:sd("MODELCTRL", "g_rockdownz01", 4, "SQ_ATCK1", 15)
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-55")
    be:FLGset(341, 1)
end
