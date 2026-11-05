if be:FLGisOn(132) ~= 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-08", 1)
else
    be:FLGset(107, 1)
    if be:FLGisOn(112) + be:FLGisOn(113) + be:FLGisOn(114) == 3 then
        be:sd("MODELCTRL", "g_d2door", 6, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
    end
end
