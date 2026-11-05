if be:DMgetCount() == 0 then
    be:MDLsetSeq("SQ_TALK")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    g_npcRamNo = be:MDLgetRamNo()
    g_messPlayerNo = be:BLTgetShootRamNo()
    if be:MDLgetRamNo() < 10 then
        be:DMsetLua("n_girumon_0" .. be:MDLgetRamNo() .. ".lua")
    else
        be:DMsetLua("n_girumon_" .. be:MDLgetRamNo() .. ".lua")
    end
    be:DMchkSD("MODELCTRL", "n_girumon", g_npcRamNo, "ISSEQNAME", "SQ_WAIT", "==0")
    be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "DISABLE")
    be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "ENABLE", 15)
    be:DMrun()
else
    be:MDLsetDMGTurn(0)
end
