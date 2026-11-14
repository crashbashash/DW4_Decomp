if be:FLGisOn(170) ~= 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-19", 1)
else
    be:FLGset(146, 1)
    if be:FLGisOn(135) + be:FLGisOn(144) + be:FLGisOn(145) == 3 then
        be:sd("MODELCTRL", "g_d2door", 6, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
    end
end
