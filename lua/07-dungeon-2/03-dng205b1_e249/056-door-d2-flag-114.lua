if be:FLGisOn(132) ~= 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-15", 1)
else
    be:FLGset(114, 1)
    if be:FLGisOn(107) + be:FLGisOn(112) + be:FLGisOn(113) == 3 then
        be:sd("MODELCTRL", "g_d2door", 6, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
    end
end
