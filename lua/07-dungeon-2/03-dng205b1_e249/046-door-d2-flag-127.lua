be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(125) == 0 then
    if be:FLGisOn(126) == 1 then
        be:sd("MODELCTRL", "g_d2door", 7, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 45)
    end
    be:FLGset(125, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(126) == 0 then
    if be:FLGisOn(125) == 1 then
        be:sd("MODELCTRL", "g_d2door", 7, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 45)
    end
    be:FLGset(126, 1)
elseif be:MDLgetRamNo() == 2 and be:FLGisOn(127) == 0 then
    be:sd("MODELCTRL", "g_d2door", 2, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_d2door", 3, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
    be:FLGset(127, 1)
elseif be:MDLgetRamNo() == 3 and be:FLGisOn(128) == 0 then
    be:sd("MODELCTRL", "g_d2door", 8, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 45)
    be:FLGset(128, 1)
end
