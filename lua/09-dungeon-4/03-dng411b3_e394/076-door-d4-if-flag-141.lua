if be:MATisAllPlayer() == 1 and be:FLGisOn(141) ~= 1 then
    if g_door04 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 3, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall04", 0, "ONHIT")
        g_door04 = 1
    end
    be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
end
