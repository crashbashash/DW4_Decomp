if be:MATisAllPlayer() == 1 and be:FLGisOn(195) ~= 1 then
    if g_door06 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 5, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall06", 0, "ONHIT")
        g_door06 = 1
    end
    if g_door07 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 6, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall07", 0, "ONHIT")
        g_door07 = 1
    end
    be:sd("GENERATER", nil, -1, "START", "GENE-09", 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-09", 1)
end
