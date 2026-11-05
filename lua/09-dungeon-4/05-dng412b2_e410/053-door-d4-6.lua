if be:MATisAllPlayer() == 1 and be:FLGisOn(269) ~= 1 then
    if g_door05 ~= 1 then
        g_door05 = 1
        be:sd("MODELCTRL", "g_d4door", 4, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall05", 0, "ONHIT")
    end
    be:sd("GENERATER", nil, -1, "START", "GENE-14", 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
end
