be:MDLsetDMGTurn(0)
if be:MDLgetHp() > 0 then
    local shootRamNo = be:BLTgetShootRamNo()
    local playerName = be:SYSgetPlayerName(shootRamNo)
    be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:MDLaddHp(-100)
    if not g_lever01z03 then
        g_lever01z03 = 1
    else
        g_lever01z03 = g_lever01z03 + 1
    end
    if be:FLGisOn(56) == 0 and g_lever01z03 == 7 then
        be:FLGset(56, 1)
    end
end
