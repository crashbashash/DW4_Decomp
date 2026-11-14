if be:MATisPlayer() == 1 and g_IFLG23 ~= 1 then
    g_lFLG23 = 1
    be:sd("ENEMY", "e_nume", -1, "SQ_ERAS")
    be:sd("GENERATER", nil, -1, "START", "GENE-99", 60)
    be:sd("GENERATER", nil, -1, "START", "GENE-106", 60)
    be:sd("GENERATER", nil, -1, "START", "GENE-110", 60)
    be:sd("GENERATER", nil, -1, "START", "GENE-115", 60)
    be:sd("GENERATER", nil, -1, "START", "GENE-119", 60)
    be:sd("GENERATER", nil, -1, "START", "GENE-122", 60)
end
