if be:MATisPlayer() == 1 then
    if be:FLGisOn(125) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-06")
        be:sd("MODELCTRL", "g_dpharocoffin", 2, "SQ_FIRE")
    end
    be:MATsetRun(0)
end
