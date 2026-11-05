be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(160) == 0 then
    be:sd("MODELCTRL", "g_d2door", 3, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
    be:FLGset(160, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(161) == 0 then
    be:sd("MODELCTRL", "g_d2door", 5, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
    be:FLGset(161, 1)
elseif be:MDLgetRamNo() == 2 and be:FLGisOn(162) == 0 then
    be:sd("MODELCTRL", "g_d2door", 11, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT", 45)
    be:FLGset(162, 1)
elseif be:MDLgetRamNo() == 3 and be:FLGisOn(163) == 0 then
    be:sd("MODELCTRL", "g_d2door", 12, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT", 45)
    be:FLGset(163, 1)
end
