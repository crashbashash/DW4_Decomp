if be:MATisAllPlayer() == 1 and be:FLGisOn(106) ~= 1 then
    if g_door04 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 3, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall04", 0, "ONHIT")
        g_door04 = 1
    end
    if g_door05 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 4, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall05", 0, "ONHIT")
        g_door05 = 1
    end
    be:sd("GENERATER", nil, -1, "START", "GENE-07", 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
end
