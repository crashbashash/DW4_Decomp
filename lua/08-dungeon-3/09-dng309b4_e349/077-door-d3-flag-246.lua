be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(246) == 0 then
    be:sd("MODELCTRL", "g_d3door", 3, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
    be:FLGset(246, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(247) == 0 then
    be:FLGset(247, 1)
    if be:FLGisOn(249) == 1 then
        be:sd("MODELCTRL", "g_d3door", 4, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    end
elseif be:MDLgetRamNo() == 2 and be:FLGisOn(248) == 0 then
    be:sd("MODELCTRL", "g_d3door", 5, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
    be:FLGset(248, 1)
elseif be:MDLgetRamNo() == 3 and be:FLGisOn(249) == 0 then
    be:FLGset(249, 1)
    if be:FLGisOn(247) == 1 then
        be:sd("MODELCTRL", "g_d3door", 4, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    end
end
