be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(136) == 0 then
    be:sd("MODELCTRL", "g_d1door", 1, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_d1door", 2, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
    be:FLGset(136, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(137) == 0 then
    be:sd("MODELCTRL", "g_d1door", 4, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    be:FLGset(137, 1)
elseif be:MDLgetRamNo() == 2 and be:FLGisOn(138) == 0 then
    be:sd("MODELCTRL", "g_d1door", 6, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
    be:FLGset(138, 1)
end
