if be:FLGisOn(127) ~= 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-07", 1)
else
    be:FLGset(106, 1)
    if be:FLGisOn(111) + be:FLGisOn(112) + be:FLGisOn(113) == 3 then
        be:sd("MODELCTRL", "g_d2door", 5, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
        be:sd("MODELCTRL", "g_d2door", 6, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
    end
end
