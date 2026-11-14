be:MDLsetDMGTurn(0)
local local_0 = 0
if be:MDLgetRamNo() == 0 and be:FLGisOn(107) == 0 then
    local_0 = 1
    be:FLGset(107, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(108) == 0 then
    local_0 = 1
    be:FLGset(108, 1)
elseif be:MDLgetRamNo() == 2 and be:FLGisOn(109) == 0 then
    local_0 = 1
    be:FLGset(109, 1)
end
if local_0 + be:FLGisOn(107) + be:FLGisOn(108) + be:FLGisOn(109) == 4 then
    be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_d1door", 3, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
end
