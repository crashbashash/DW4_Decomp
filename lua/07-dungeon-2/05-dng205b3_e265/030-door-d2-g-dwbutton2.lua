be:MDLsetDMGTurn(0)
local shootRamNo = be:BLTgetShootRamNo()
local playerName = be:SYSgetPlayerName(shootRamNo)
local local_2 = 0
if be:SYSgetPlayerNinzu() == 1 then
    local_2 = 270
else
    local_2 = 15
end
if be:MDLgetRamNo() == 0 then
    if be:FLGisOn(208) == 0 then
        be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
        be:MDLsetSeq("SQ_SWON")
        be:FLGset(208, 1)
        if be:FLGisOn(209) == 1 then
            be:sd("MODELCTRL", "g_d2door", 7, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 45)
            be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
        else
            be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_SWOF", local_2)
        end
    end
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(209) == 0 then
    be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:FLGset(209, 1)
    if be:FLGisOn(208) == 1 then
        be:sd("MODELCTRL", "g_d2door", 7, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 45)
        be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
    else
        be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_SWOF", local_2)
    end
end
