if be:MATisAllPlayer() == 1 and be:FLGisOn(224) ~= 1 then
    if g_door11 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 10, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall11", 0, "ONHIT")
        g_door11 = 1
    end
    be:sd("GENERATER", nil, -1, "START", "GENE-14", 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
end
