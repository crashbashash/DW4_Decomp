if be:FLGisOn(169) ~= 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-06", 1)
else
    be:FLGset(133, 1)
    if be:FLGisOn(141) + be:FLGisOn(142) + be:FLGisOn(143) == 3 then
        be:sd("MODELCTRL", "g_d2door", 4, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    end
end
