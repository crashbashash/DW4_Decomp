be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 then
    if be:FLGisOn(207) == 1 then
        be:sd("MODELCTRL", "g_d3door", 0, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    end
    be:FLGset(206, 1)
elseif be:MDLgetRamNo() == 1 then
    if be:FLGisOn(206) == 1 then
        be:sd("MODELCTRL", "g_d3door", 0, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    end
    be:FLGset(207, 1)
elseif be:MDLgetRamNo() == 2 then
    be:sd("MODELCTRL", "g_d3door", 5, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_d3door", 6, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
    be:FLGset(208, 1)
elseif be:MDLgetRamNo() == 3 then
    be:sd("MODELCTRL", "g_d3door", 9, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT", 45)
    be:FLGset(209, 1)
end
