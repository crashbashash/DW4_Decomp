be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 then
    if be:FLGisOn(147) + be:FLGisOn(148) + be:FLGisOn(149) == 3 then
        be:sd("MODELCTRL", "g_d4door", 0, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    end
    be:FLGset(146, 1)
elseif be:MDLgetRamNo() == 1 then
    if be:FLGisOn(146) + be:FLGisOn(148) + be:FLGisOn(149) == 3 then
        be:sd("MODELCTRL", "g_d4door", 0, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    end
    be:FLGset(147, 1)
elseif be:MDLgetRamNo() == 2 then
    if be:FLGisOn(146) + be:FLGisOn(147) + be:FLGisOn(149) == 3 then
        be:sd("MODELCTRL", "g_d4door", 0, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    end
    be:FLGset(148, 1)
elseif be:MDLgetRamNo() == 3 then
    if be:FLGisOn(146) + be:FLGisOn(147) + be:FLGisOn(148) == 3 then
        be:sd("MODELCTRL", "g_d4door", 0, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    end
    be:FLGset(149, 1)
elseif be:MDLgetRamNo() == 4 then
    if be:FLGisOn(151) == 1 then
        be:sd("MODELCTRL", "g_d4door", 12, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT", 45)
    end
    be:FLGset(150, 1)
elseif be:MDLgetRamNo() == 5 then
    if be:FLGisOn(150) == 1 then
        be:sd("MODELCTRL", "g_d4door", 12, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT", 45)
    end
    be:FLGset(151, 1)
end
