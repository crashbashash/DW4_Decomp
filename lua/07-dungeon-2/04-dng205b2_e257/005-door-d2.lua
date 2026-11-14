be:MDLsetDMGTurn(0)
local local_0 = 0
if be:MDLgetRamNo() == 0 and be:FLGisOn(160) == 0 then
    local_0 = 1
    be:FLGset(160, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(161) == 0 then
    local_0 = 1
    be:FLGset(161, 1)
elseif be:MDLgetRamNo() == 2 and be:FLGisOn(162) == 0 then
    local_0 = 1
    be:FLGset(162, 1)
elseif be:MDLgetRamNo() == 3 and be:FLGisOn(163) == 0 then
    local_0 = 1
    be:FLGset(163, 1)
end
if local_0 + be:FLGisOn(160) + be:FLGisOn(161) + be:FLGisOn(162) + be:FLGisOn(163) == 5 then
    if be:SYSgetPlayerNinzu() == 4 then
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
    end
    if be:SYSgetPlayerNinzu() >= 3 then
        be:sd("MODELCTRL", "g_dbutton2", 3, "SQ_ONLOOP")
    end
    if be:SYSgetPlayerNinzu() >= 2 then
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_ONLOOP")
    end
    be:sd("MODELCTRL", "g_d2door", 5, "SQ_SWOF", 15)
    be:sd("HITLANDMODEL", "doorwall06", 0, "ONHIT")
    g_door06 = 0
    be:sd("MODELCTRL", "g_d2door", 6, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
end
