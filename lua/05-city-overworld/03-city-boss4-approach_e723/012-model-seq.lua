if be:DMgetCount() == 0 then
    be:MDLsetDMGTurn(0)
    be:MDLsetSeq("SQ_TALK")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:sd("GENERATER", nil, -1, "ONFREEZE")
    g_npcRamNo = be:MDLgetRamNo()
    g_messPlayerNo = be:BLTgetShootRamNo()
    be:sd("MODELCTRL", local_0, g_messPlayerNo, "SQ_WAIT", 0)
    be:DMchkSD("PLAYER", local_0, g_messPlayerNo, "ISSEQNAME", "SQ_WAIT", "==0")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    if be:MDLgetRamNo() < 10 then
        be:DMsetLua("n_recorder_0" .. be:MDLgetRamNo() .. ".lua")
    else
        be:DMsetLua("n_recorder_" .. be:MDLgetRamNo() .. ".lua")
    end
    be:DMchkSD("MODELCTRL", "n_recorder", g_npcRamNo, "ISSEQNAME", "SQ_WAIT", "==0")
    be:DMsetSD("GENERATER", nil, -1, "OFFREEZE")
    be:DMrun()
else
    be:MDLsetDMGTurn(0)
end
