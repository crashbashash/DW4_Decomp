be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(113) == 0 then
    be:sd("MODELCTRL", "g_d1door", 1, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT", 45)
    be:FLGset(113, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(114) == 0 then
    be:sd("MODELCTRL", "g_d1door", 3, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
    be:FLGset(114, 1)
end
