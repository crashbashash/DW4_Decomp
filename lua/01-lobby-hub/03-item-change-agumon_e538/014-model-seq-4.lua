if be:DMgetCount() == 0 then
    be:MDLsetSeq("SQ_TALK")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    g_npcRamNo = be:MDLgetRamNo()
    g_messPlayerNo = be:BLTgetShootRamNo()
    be:sd("MODELCTRL", local_2, g_messPlayerNo, "SQ_WAIT", 0)
    be:DMchkSD("PLAYER", local_2, g_messPlayerNo, "ISSEQNAME", "SQ_WAIT", "==0")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    if be:SYSgetDifficulty() == 0 then
        local_0 = "n"
    elseif be:SYSgetDifficulty() == 1 then
        local_0 = "h"
    else
        local_0 = "v"
    end
    if be:MDLgetRamNo() < 10 then
        be:DMsetLua("n_weregaru_0" .. be:MDLgetRamNo() .. local_0 .. ".lua")
    else
        be:DMsetLua("n_weregaru_" .. be:MDLgetRamNo() .. local_0 .. ".lua")
    end
    be:DMchkSD("MODELCTRL", "n_weregaru", g_npcRamNo, "ISSEQNAME", "SQ_WAIT", "==0")
    be:DMsetSD("MODELCTRL", "n_weregaru", g_npcRamNo, "MOVETRANS", be:MDLgetPosStr(0, 0, 0) .. "/" .. local_1)
    be:DMrun()
else
    be:MDLsetDMGTurn(0)
end
