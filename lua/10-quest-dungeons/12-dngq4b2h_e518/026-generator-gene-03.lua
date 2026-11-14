if be:MATisPlayer() == 1 then
    if be:FLGisOn(122) ~= 1 then
        be:sd("MODELCTRL", "g_dpharocoffin", 0, "SQ_FIRE")
        be:sd("GENERATER", nil, -1, "START", "GENE-03")
    end
    be:MATsetRun(0)
end
