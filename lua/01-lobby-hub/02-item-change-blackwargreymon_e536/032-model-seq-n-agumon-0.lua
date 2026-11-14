local local_0
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
    if be:SYSgetDifficulty() == 0 then
        local_0 = "n"
    elseif be:SYSgetDifficulty() == 1 then
        local_0 = "h"
    else
        local_0 = "v"
    end
    if be:MDLgetRamNo() < 2 then
        be:DMsetLua("n_agumon_0" .. be:MDLgetRamNo() .. local_0 .. ".lua")
    else
        be:DMsetLua("n_agumon_0" .. be:MDLgetRamNo() .. ".lua")
    end
    be:DMchkSD("MODELCTRL", "n_agumon", g_npcRamNo, "ISSEQNAME", "SQ_WAIT", "==0")
    be:DMsetSD("MODELCTRL", "n_agumon", g_npcRamNo, "MOVETRANS", be:MDLgetPosStr(0, 0, 0) .. "/" .. rotStr)
    be:DMrun()
else
    be:MDLsetDMGTurn(0)
end
