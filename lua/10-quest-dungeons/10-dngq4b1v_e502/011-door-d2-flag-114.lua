be:MDLsetDMGTurn(0)
local shootRamNo = be:BLTgetShootRamNo()
local playerName = be:SYSgetPlayerName(shootRamNo)
local local_2
if be:SYSgetPlayerNinzu() > 1 then
    local_2 = 15
else
    local_2 = 120
end
if be:MDLgetRamNo() == 0 and be:FLGisOn(117) == 0 then
    be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:FLGset(117, 1)
    if be:FLGisOn(118) == 1 then
        be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
        if be:FLGisOn(119) == 0 then
            be:sd("MODELCTRL", "g_d2door", 11, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT", 45)
            be:FLGset(114, 1)
        else
            be:sd("MODELCTRL", "g_d2door", 10, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT", 45)
            be:FLGset(113, 1)
        end
    elseif be:FLGisOn(119) == 0 then
        be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_SWOF", local_2)
    end
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(118) == 0 then
    be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:FLGset(118, 1)
    if be:FLGisOn(117) == 1 then
        be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
        if be:FLGisOn(119) == 0 then
            be:sd("MODELCTRL", "g_d2door", 11, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT", 45)
            be:FLGset(114, 1)
        else
            be:sd("MODELCTRL", "g_d2door", 10, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT", 45)
            be:FLGset(113, 1)
        end
    elseif be:FLGisOn(119) == 0 then
        be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_SWOF", local_2)
    end
end
