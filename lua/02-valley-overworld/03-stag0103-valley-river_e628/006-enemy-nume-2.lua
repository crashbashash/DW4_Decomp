if be:MATisPlayer() == 1 and g_lFLG21 ~= 1 then
    g_lFLG21 = 1
    be:sd("ENEMY", "e_nume", -1, "SQ_ERAS")
    be:sd("GENERATER", nil, -1, "START", "GENE-69", 60)
    be:sd("GENERATER", nil, -1, "START", "GENE-70", 60)
    be:sd("GENERATER", nil, -1, "START", "GENE-77", 60)
    be:sd("GENERATER", nil, -1, "START", "GENE-80", 60)
else
end
