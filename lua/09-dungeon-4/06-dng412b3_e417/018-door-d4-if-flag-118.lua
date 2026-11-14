if be:MATisAllPlayer() == 1 and be:FLGisOn(118) ~= 1 then
    if g_door09 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 8, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall09", 0, "ONHIT")
        g_door09 = 1
    end
    if g_door10 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 9, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall10", 0, "ONHIT")
        g_door10 = 1
    end
    be:sd("GENERATER", nil, -1, "START", "GENE-19", 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-23")
end
