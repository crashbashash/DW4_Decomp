if be:MATisPlayer() == 1 and be:FLGisOn(104) ~= 1 and g_gene05 ~= 1 then
    be:sd("MODELCTRL", "g_dpharocoffin", 0, "SQ_FIRE", 1)
    be:sd("GENERATER", nil, -1, "START", "GENE-05", 1)
    g_gene05 = 1
end
