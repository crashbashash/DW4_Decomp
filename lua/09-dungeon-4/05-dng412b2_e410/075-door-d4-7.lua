if be:MATisAllPlayer() == 1 and be:FLGisOn(264) ~= 1 then
    if g_door02 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 1, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall02", 0, "ONHIT")
        g_door02 = 1
    end
    be:sd("GENERATER", nil, -1, "START", "GENE-09", 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
end
