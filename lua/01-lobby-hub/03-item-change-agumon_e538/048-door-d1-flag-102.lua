be:MDLsetDMGTurn(0)
local shootRamNo = be:BLTgetShootRamNo()
local playerName = be:SYSgetPlayerName(shootRamNo)
local local_2
if be:MDLgetRamNo() == 0 and be:FLGisOn(102) == 0 then
    be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_d1door", 0, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    be:FLGset(102, 1)
    if be:FLGisOn(104) ~= 1 then
        for ramNo = 0, 1 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(103) == 0 then
    be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_d1door", 1, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT", 45)
    be:FLGset(103, 1)
    if be:FLGisOn(105) ~= 1 then
        for ramNo = 2, 3 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
end
