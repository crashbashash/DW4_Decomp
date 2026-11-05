if be:MATisAllPlayer() == 1 and be:FLGisOn(196) ~= 1 then
    if g_door10 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 9, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall10", 0, "ONHIT")
        g_door10 = 1
    end
    be:sd("GENERATER", nil, -1, "START", "GENE-10", 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
end
