be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(120) == 0 then
    if be:FLGisOn(121) == 1 then
        be:sd("MODELCTRL", "g_dtdoor", 9, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT", 45)
    end
    be:FLGset(120, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(121) == 0 then
    if be:FLGisOn(120) == 1 then
        be:sd("MODELCTRL", "g_dtdoor", 9, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT", 45)
    end
    be:FLGset(121, 1)
elseif be:MDLgetRamNo() == 2 and be:FLGisOn(122) == 0 then
    be:sd("MODELCTRL", "g_dtdoor", 6, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 45)
    be:FLGset(122, 1)
elseif be:MDLgetRamNo() == 3 and be:FLGisOn(123) == 0 then
    be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT", 45)
    be:FLGset(123, 1)
elseif be:MDLgetRamNo() == 4 and be:FLGisOn(126) == 0 then
    be:sd("MODELCTRL", "g_dtdoor", 13, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_dtdoor", 14, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT", 45)
    be:FLGset(126, 1)
elseif be:MDLgetRamNo() == 5 and be:FLGisOn(127) == 0 then
    be:sd("MODELCTRL", "g_dtdoor", 17, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall18", 0, "OFFHIT", 45)
    be:FLGset(127, 1)
elseif be:MDLgetRamNo() == 6 and be:FLGisOn(128) == 0 then
    be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
    be:FLGset(128, 1)
end
