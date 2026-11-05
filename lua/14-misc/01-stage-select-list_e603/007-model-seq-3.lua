if be:DMgetCount() == 0 then
    be:MDLsetSeq("SQ_TALK")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    g_npcRamNo = be:MDLgetRamNo()
    g_messPlayerNo = be:BLTgetShootRamNo()
    be:sd("MODELCTRL", local_1, g_messPlayerNo, "SQ_WAIT", 0)
    be:DMchkSD("PLAYER", local_1, g_messPlayerNo, "ISSEQNAME", "SQ_WAIT", "==0")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    if be:MDLgetRamNo() < 10 then
        be:DMsetLua("n_leomon_0" .. be:MDLgetRamNo() .. ".lua")
    else
        be:DMsetLua("n_leomon_" .. be:MDLgetRamNo() .. ".lua")
    end
    be:DMchkSD("MODELCTRL", "n_leomon", g_npcRamNo, "ISSEQNAME", "SQ_WAIT", "==0")
    be:DMsetSD("MODELCTRL", "n_leomon", g_npcRamNo, "MOVETRANS", be:MDLgetPosStr(0, 0, 0) .. "/" .. local_0)
    be:DMrun()
else
    be:MDLsetDMGTurn(0)
end
