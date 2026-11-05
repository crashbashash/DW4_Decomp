if be:MDLgetRamNo() == 0 and be:FLGisOn(145) ~= 1 then
    be:FLGset(145, 1)
    if be:FLGisOn(146) + be:FLGisOn(147) + be:FLGisOn(148) == 3 then
        be:sd("MODELCTRL", "g_d2door", 4, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
        be:FLGset(135, 1)
    else
    end
end
if be:MDLgetRamNo() == 1 and be:FLGisOn(146) ~= 1 then
    be:FLGset(146, 1)
    if be:FLGisOn(145) + be:FLGisOn(147) + be:FLGisOn(148) == 3 then
        be:sd("MODELCTRL", "g_d2door", 4, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
        be:FLGset(135, 1)
    else
    end
end
if be:MDLgetRamNo() == 2 and be:FLGisOn(147) ~= 1 then
    be:FLGset(147, 1)
    if be:FLGisOn(145) + be:FLGisOn(146) + be:FLGisOn(148) == 3 then
        be:sd("MODELCTRL", "g_d2door", 4, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
        be:FLGset(135, 1)
    else
    end
end
if be:MDLgetRamNo() == 3 and be:FLGisOn(148) ~= 1 and be:FLGisOn(145) + be:FLGisOn(146) + be:FLGisOn(147) == 3 then
    be:sd("MODELCTRL", "g_d2door", 4, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    be:FLGset(135, 1)
end
