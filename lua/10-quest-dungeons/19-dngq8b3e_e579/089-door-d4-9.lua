if be:MDLgetRamNo() == 0 then
    be:FLGset(237, 1)
    be:sd("MODELCTRL", "g_d4door", 1, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT", 45)
    if be:FLGisOn(238) == 1 then
        be:sd("MODELCTRL", "g_d4door", 2, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
    else
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(238, 1)
    if be:FLGisOn(237) == 1 then
        be:sd("MODELCTRL", "g_d4door", 2, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
    else
    end
end
if be:MDLgetRamNo() == 2 then
    be:FLGset(239, 1)
    if be:FLGisOn(240) == 1 then
        be:sd("MODELCTRL", "g_d4door", 4, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    else
    end
end
if be:MDLgetRamNo() == 3 then
    be:FLGset(240, 1)
    be:sd("MODELCTRL", "g_d4door", 3, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
    if be:FLGisOn(239) == 1 then
        be:sd("MODELCTRL", "g_d4door", 4, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    else
    end
end
if be:MDLgetRamNo() == 4 then
    be:FLGset(241, 1)
    be:sd("MODELCTRL", "g_dbarrierw9", 1, "SQ_POWEROF", 30)
    be:sd("HITLANDMODEL", "barrierwall3", 0, "OFFHIT", 30)
    if be:FLGisOn(242) == 1 then
        be:sd("MODELCTRL", "g_dbarrierp", 10, "SQ_POWEROF", 30)
        be:sd("MODELCTRL", "g_dbarrierp", 11, "SQ_POWEROF", 30)
        be:sd("MODELCTRL", "g_dbarrierp", 12, "SQ_POWEROF", 30)
        be:sd("MODELCTRL", "g_dbarrierp", 13, "SQ_POWEROF", 30)
    else
    end
end
if be:MDLgetRamNo() == 5 then
    be:FLGset(242, 1)
    be:sd("MODELCTRL", "g_dbarrierw9", 0, "SQ_POWEROF", 30)
    be:sd("HITLANDMODEL", "barrierwall4", 0, "OFFHIT", 30)
    if be:FLGisOn(241) == 1 then
        be:sd("MODELCTRL", "g_dbarrierp", 10, "SQ_POWEROF", 30)
        be:sd("MODELCTRL", "g_dbarrierp", 11, "SQ_POWEROF", 30)
        be:sd("MODELCTRL", "g_dbarrierp", 12, "SQ_POWEROF", 30)
        be:sd("MODELCTRL", "g_dbarrierp", 13, "SQ_POWEROF", 30)
    else
    end
end
if be:MDLgetRamNo() == 6 then
    be:FLGset(243, 1)
    be:sd("MODELCTRL", "g_d4door", 8, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 45)
elseif be:MDLgetRamNo() == 7 then
    be:FLGset(244, 1)
    be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 13, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT", 45)
elseif be:MDLgetRamNo() == 8 then
    be:FLGset(245, 1)
    be:sd("MODELCTRL", "g_d4door", 16, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall17", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_d4door", 17, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall18", 0, "OFFHIT", 45)
elseif be:MDLgetRamNo() == 9 then
    be:FLGset(246, 1)
    be:sd("MODELCTRL", "g_d4door", 18, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall19", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_d4door", 19, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall20", 0, "OFFHIT", 45)
end
