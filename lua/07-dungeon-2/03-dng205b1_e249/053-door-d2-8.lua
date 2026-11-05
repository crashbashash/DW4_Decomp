if be:FLGisOn(131) ~= 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-12", 1)
else
    be:FLGset(111, 1)
    if be:FLGisOn(104) + be:FLGisOn(109) + be:FLGisOn(110) == 3 then
        be:sd("MODELCTRL", "g_d2door", 4, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
        be:sd("MODELCTRL", "g_d2door", 5, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
    end
end
