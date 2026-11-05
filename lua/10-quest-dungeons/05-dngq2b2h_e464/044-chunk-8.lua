if be:MATisPlayer() == 1 then
    if be:FLGisOn(127) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-08")
        be:sd("MODELCTRL", "g_dpharocoffin", 0, "SQ_FIRE")
    end
    be:MATsetRun(0)
end
