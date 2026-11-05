if be:MATisPlayer() == 1 and be:FLGisOn(339) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_rockdownz01", 2, "SQ_ATCK1", 15)
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-53")
    be:FLGset(339, 1)
end
