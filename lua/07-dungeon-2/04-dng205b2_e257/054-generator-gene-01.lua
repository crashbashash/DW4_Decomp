if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    if g_pharaoh01 ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-01")
        be:sd("MODELCTRL", "g_dpharocoffin", 0, "SQ_FIRE")
        g_pharaoh01 = 1
    end
end
