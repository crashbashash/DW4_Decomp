if be:MATisAllPlayer() == 1 and be:FLGisOn(220) ~= 1 then
    if g_door08 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 7, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall08", 0, "ONHIT")
        g_door08 = 1
    end
    be:sd("GENERATER", nil, -1, "START", "GENE-10", 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
end
