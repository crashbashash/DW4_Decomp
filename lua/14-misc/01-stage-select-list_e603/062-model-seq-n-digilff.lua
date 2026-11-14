if be:DMgetCount() == 0 then
    local rotStr = be:MDLgetRotStr(0, 0, 0)
    be:MDLsetSeq("SQ_TALK")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    g_npcRamNo = be:MDLgetRamNo()
    g_messPlayerNo = be:BLTgetShootRamNo()
    local playerName = be:SYSgetPlayerName(g_messPlayerNo)
    be:sd("MODELCTRL", playerName, g_messPlayerNo, "SQ_WAIT", 0)
    be:DMchkSD("PLAYER", playerName, g_messPlayerNo, "ISSEQNAME", "SQ_WAIT", "==0")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    if be:MDLgetRamNo() < 10 then
        be:DMsetLua("n_digilff_0" .. be:MDLgetRamNo() .. ".lua")
    else
        be:DMsetLua("n_digilff_" .. be:MDLgetRamNo() .. ".lua")
    end
    be:DMchkSD("MODELCTRL", "n_digilff", g_npcRamNo, "ISSEQNAME", "SQ_WAIT", "==0")
    be:DMsetSD("MODELCTRL", "n_digilff", g_npcRamNo, "MOVETRANS", be:MDLgetPosStr(0, 0, 0) .. "/" .. rotStr)
    be:DMrun()
else
    be:MDLsetDMGTurn(0)
end
