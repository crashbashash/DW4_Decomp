if funcTechWazaHitCheck() == 1 then
elseif be:DMgetCount() == 0 then
    be:MDLsetDMGTurn(0)
    be:MDLsetSeq("SQ_SDMG")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    local local_0
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            local local_4
            for itemId = 0, 11 do
                be:SYSctlDiskFolder("SET", playerIndex, itemId, 9)
            end
        end
    end
    g_npcRamNo = be:MDLgetRamNo()
    g_messPlayerNo = be:BLTgetShootRamNo()
    funcOpenMessage("mess")
    mswk80004 = "TALKFONT01/font00/I<47>"
    funcOneMessage(mswk80004)
    funcCloseMessage("mess")
    be:DMrun()
else
    be:MDLsetDMGTurn(0)
end
