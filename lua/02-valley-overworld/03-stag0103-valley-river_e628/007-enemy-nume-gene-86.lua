if be:MATisPlayer() == 1 and g_lFLG22 ~= 1 then
    g_lFLG22 = 1
    be:sd("ENEMY", "e_nume", -1, "SQ_ERAS")
    be:sd("GENERATER", nil, -1, "START", "GENE-86", 60)
    be:sd("GENERATER", nil, -1, "START", "GENE-92", 60)
    be:sd("GENERATER", nil, -1, "START", "GENE-95", 60)
    be:sd("MODELCTRL", "g_annihilativebomz06", 0, "SQ_ERAS")
    be:sd("MODELCTRL", "g_annihilativebomz06", 1, "SQ_ERAS")
    be:sd("MODELCTRL", "g_dumperz06", 0, "SQ_ERAS")
    be:sd("MODELCTRL", "g_facteyez06", 0, "SQ_ERAS")
    be:sd("MODELCTRL", "g_facteyez06", 1, "SQ_ERAS")
    be:sd("MODELCTRL", "g_factgatez06", 0, "SQ_ERAS")
    be:sd("MODELCTRL", "g_facttowerz06", 0, "SQ_ERAS")
    be:sd("MODELCTRL", "g_facttowerz06", 1, "SQ_ERAS")
    be:sd("MODELCTRL", "g_facttowerz06", 2, "SQ_ERAS")
    be:sd("MODELCTRL", "g_facttowerz06", 3, "SQ_ERAS")
    be:sd("MODELCTRL", "g_facttowerz06", 4, "SQ_ERAS")
    be:sd("MODELCTRL", "g_facttowerz06", 5, "SQ_ERAS")
    be:sd("MODELCTRL", "g_shelfz06", 0, "SQ_ERAS")
    be:sd("MODELCTRL", "g_shelfz06", 1, "SQ_ERAS")
else
end
