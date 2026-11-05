if be:MATisAllPlayer() == 1 and be:FLGisOn(106) ~= 1 and be:FLGisOn(140) ~= 1 and g_door08 ~= 1 then
    be:sd("MODELCTRL", "g_d4door", 7, "SQ_SWOF")
    be:sd("HITLANDMODEL", "doorwall08", 0, "ONHIT")
    g_door08 = 1
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    if be:FLGisOn(140) == 1 and be:FLGisOn(106) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-07", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-07", 1)
