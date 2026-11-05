be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(134) == 0 then
    be:sd("MODELCTRL", "g_d3door", 5, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
    be:FLGset(134, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(135) == 0 then
    be:sd("MODELCTRL", "g_d3door", 4, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    be:FLGset(135, 1)
end
