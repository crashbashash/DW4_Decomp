if funcTechWazaHitCheck() == 1 then
elseif be:DMgetCount() == 0 then
    be:MDLsetDMGTurn(0)
    be:MDLsetSeq("SQ_SDMG")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    for local_1 = 0, 3 do
        if be:SYSisJoinPlayer(local_1) == 1 then
            be:SYSctlBit("SET", local_1, 9999999)
        end
    end
    g_npcRamNo = be:MDLgetRamNo()
    g_messPlayerNo = be:BLTgetShootRamNo()
    funcOpenMessage("mess")
    mswk80003 = "TALKFONT01/font00/I<46>"
    funcOneMessage(mswk80003)
    funcCloseMessage("mess")
    be:DMrun()
else
    be:MDLsetDMGTurn(0)
end
