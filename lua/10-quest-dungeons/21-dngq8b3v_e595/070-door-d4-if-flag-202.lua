if be:MATisAllPlayer() == 1 then
    if g_door15 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 14, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall15", 0, "ONHIT")
        g_door15 = 1
    end
    if be:FLGisOn(202) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-16", 1)
    end
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-16", 1)
end
