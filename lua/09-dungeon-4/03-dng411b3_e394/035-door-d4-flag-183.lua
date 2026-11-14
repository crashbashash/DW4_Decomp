be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(183) == 0 then
    be:sd("MODELCTRL", "g_d4door", 5, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
    be:FLGset(183, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(184) == 0 then
    be:sd("MODELCTRL", "g_d4door", 6, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_d4door", 7, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 45)
    be:FLGset(184, 1)
end
