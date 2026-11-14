be:MDLsetDMGTurn(0)
local shootRamNo = be:BLTgetShootRamNo()
local playerName = be:SYSgetPlayerName(shootRamNo)
while be:FLGisOn(121) ~= 1 and be:DMgetCount() == 0 do
    local local_2 = 0
    local local_3
    g_npcRamNo = be:MDLgetRamNo()
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
    be:DMchkSD("PLAYER", playerName, shootRamNo, "ISSEQNAME", "SQ_WAIT", "==0")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN")
    g_talk = "mess"
    g_page = 0
    g_messPlayerNo = 0
    if local_2 == 0 then
        g_putItemSelection = g_putItemSelection + 1
        if not g_putItemList[g_putItemSelection] then
            g_putItemSelection = 1
        end
        local_3 = g_putItemList[g_putItemSelection]
        if local_3.category == "flag" then
            if be:SYSctlFlagFolder("IS", local_3.number) == 1 then
                local_2 = 1
            end
        end
    end
end
