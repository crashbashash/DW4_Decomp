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
elseif be:MDLgetRamNo() == 4 and be:FLGisOn(164) == 0 then
    be:sd("MODELCTRL", "g_d2door", 9, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT", 45)
    be:FLGset(164, 1)
end
if local_0 + be:FLGisOn(160) + be:FLGisOn(161) + be:FLGisOn(162) + be:FLGisOn(163) == 5 then
    if be:SYSisJoinPlayer(3) == 1 then
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
    end
    if be:SYSisJoinPlayer(2) == 1 then
        be:sd("MODELCTRL", "g_dbutton2", 3, "SQ_ONLOOP")
    end
    if be:SYSisJoinPlayer(1) == 1 then
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_ONLOOP")
    end
    be:sd("MODELCTRL", "g_d2door", 5, "SQ_SWOF", 15)
    be:sd("HITLANDMODEL", "doorwall06", 0, "ONHIT")
    g_door06 = 0
    be:sd("MODELCTRL", "g_d2door", 6, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
end
