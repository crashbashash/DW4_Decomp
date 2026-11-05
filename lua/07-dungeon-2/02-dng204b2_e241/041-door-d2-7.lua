if be:FLGisOn(169) ~= 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-15", 1)
else
    be:FLGset(142, 1)
    if be:FLGisOn(133) + be:FLGisOn(141) + be:FLGisOn(143) == 3 then
        be:sd("MODELCTRL", "g_d2door", 4, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    end
end
