be:MDLsetDMGTurn(0)
local shootRamNo = be:BLTgetShootRamNo()
local playerName = be:SYSgetPlayerName(shootRamNo)
if be:MDLgetRamNo() == 0 and be:FLGisOn(129) == 0 then
    be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_dtdoor", 8, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 45)
    be:FLGset(129, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(130) == 0 then
    be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_dtdoor", 16, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall17", 0, "OFFHIT", 45)
    be:FLGset(130, 1)
end
