be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(165) == 0 then
    local shootRamNo = be:BLTgetShootRamNo()
    local playerName = be:SYSgetPlayerName(shootRamNo)
    be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_d2door", 0, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_d2door", 1, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT", 45)
    be:FLGset(165, 1)
end
