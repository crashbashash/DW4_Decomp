if be:FLGisOn(169) ~= 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-14", 1)
else
    be:FLGset(141, 1)
    if be:FLGisOn(133) + be:FLGisOn(142) + be:FLGisOn(143) == 3 then
        be:sd("MODELCTRL", "g_d2door", 4, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    end
end
