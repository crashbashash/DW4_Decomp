if be:MATisPlayer() == 1 and g_lFLG20 ~= 1 then
    g_lFLG20 = 1
    be:sd("ENEMY", "e_nume", -1, "SQ_ERAS")
    be:sd("GENERATER", nil, -1, "START", "GENE-41", 60)
    be:sd("GENERATER", nil, -1, "START", "GENE-48", 60)
else
end
