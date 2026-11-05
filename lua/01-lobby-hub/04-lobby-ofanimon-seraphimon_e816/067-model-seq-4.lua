if be:DMgetCount() == 0 then
    be:MDLsetDMGTurn(0)
    be:MDLsetSeq("SQ_TALK")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    g_npcRamNo = be:MDLgetRamNo()
    g_messPlayerNo = be:BLTgetShootRamNo()
    if be:MDLgetRamNo() < 10 then
        be:DMsetLua("n_seraph_0" .. be:MDLgetRamNo() .. ".lua")
    else
        be:DMsetLua("n_seraph_" .. be:MDLgetRamNo() .. ".lua")
    end
    be:DMrun()
else
    be:MDLsetDMGTurn(0)
end
