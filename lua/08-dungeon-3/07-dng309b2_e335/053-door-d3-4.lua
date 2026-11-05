be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(154) == 0 then
    be:sd("MODELCTRL", "g_d3door", 2, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
    be:FLGset(154, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(155) == 0 then
    be:sd("MODELCTRL", "g_d3door", 3, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
    be:FLGset(155, 1)
end
