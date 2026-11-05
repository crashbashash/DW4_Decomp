if be:MATisPlayer() == 1 and be:FLGisOn(123) ~= 1 and g_gene04 ~= 1 then
    be:sd("MODELCTRL", "g_dpharocoffin", 1, "SQ_FIRE", 1)
    be:sd("GENERATER", nil, -1, "START", "GENE-04", 1)
    g_gene04 = 1
end
