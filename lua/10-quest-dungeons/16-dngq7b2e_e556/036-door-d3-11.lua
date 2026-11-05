if be:MDLgetRamNo() == 0 then
    be:FLGset(249, 1)
    be:sd("MODELCTRL", "g_d3door", 12, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT", 45)
    if be:FLGisOn(252) ~= 1 then
        be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON")
        be:FLGset(252, 1)
        be:sd("MODELCTRL", "g_d3door", 14, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT", 45)
    else
    end
end
if be:MDLgetRamNo() == 1 then
    be:FLGset(250, 1)
    be:sd("MODELCTRL", "g_d3door", 15, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall16", 0, "OFFHIT", 45)
    if be:FLGisOn(251) ~= 1 then
        be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
        be:FLGset(251, 1)
        be:sd("MODELCTRL", "g_d3door", 13, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT", 45)
    else
    end
end
if be:MDLgetRamNo() == 2 then
    be:FLGset(251, 1)
    be:sd("MODELCTRL", "g_d3door", 13, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT", 45)
elseif be:MDLgetRamNo() == 3 then
    be:FLGset(252, 1)
    be:sd("MODELCTRL", "g_d3door", 14, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT", 45)
end
