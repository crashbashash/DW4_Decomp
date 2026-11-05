be:MDLsetDMGTurn(0)
while be:FLGisOn(121) ~= 1 and be:DMgetCount() == 0 do
    g_npcRamNo = be:MDLgetRamNo()
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:DMchkSD("PLAYER", local_1, local_0, "ISSEQNAME", "SQ_WAIT", "==0")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN")
    g_talk = "mess"
    g_page = 0
    g_messPlayerNo = 0
    while local_2 == 0 do
        g_putItemSelection = g_putItemSelection + 1
        if not g_putItemList[g_putItemSelection] then
            g_putItemSelection = 1
        end
        local_3 = g_putItemList[g_putItemSelection]
        while local_3.category == "flag" do
            while be:SYSctlFlagFolder("IS", local_3.number) == 1 do
                local_2 = 1
            end
        end
    end
end
