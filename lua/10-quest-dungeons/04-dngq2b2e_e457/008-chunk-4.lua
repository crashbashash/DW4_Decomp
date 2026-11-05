if be:MATisPlayer() == 1 then
    if be:FLGisOn(126) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-07")
        be:sd("MODELCTRL", "g_dpharocoffin", 1, "SQ_FIRE")
    end
    be:MATsetRun(0)
end
