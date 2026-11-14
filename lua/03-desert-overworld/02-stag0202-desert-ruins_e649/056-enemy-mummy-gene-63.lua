if be:MATisAllPlayer() == 1 and g_IFLG01 ~= 1 then
    be:sd("ENEMY", "e_mummy", -1, "SQ_ERAS")
    be:sd("ENEMY", "e_tyrano", -1, "SQ_ERAS")
    be:sd("GENERATER", nil, -1, "START", "GENE-63")
    g_IFLG01 = 1
end
