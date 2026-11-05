g_npcRamNo = be:MDLgetRamNo()
g_messPlayerNo = be:BLTgetShootRamNo()
if be:DMgetCount() == 0 then
    be:MDLsetDMGTurn(0)
    be:MDLsetSeq("SQ_TALK")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:sd("GENERATER", nil, -1, "ONFREEZE")
    be:sd("MODELCTRL", local_0, g_messPlayerNo, "SQ_WAIT", 0)
    be:DMchkSD("PLAYER", local_0, g_messPlayerNo, "ISSEQNAME", "SQ_WAIT", "==0")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    mswk65019 = "TALKFONT01/font00/I<9>"
    be:FLGset(291, 1)
    if be:MDLisLive("j_map309b1", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map309b1", 0, "GENERATE", "SQ_OPEN")
    end
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 and be:MDLisLive("j_mapcur", local_2) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_2, "GENERATE")
        end
    end
    funcOpenMessage("mess", "n_recorderdng")
    funcOneMessage(mswk65019)
    funcCloseMessage("mess", "n_recorderdng")
    be:DMchkSD("MODELCTRL", "n_recorderdng", g_npcRamNo, "ISSEQNAME", "SQ_WAIT", "==0")
    be:DMsetSD("GENERATER", nil, -1, "OFFREEZE")
    be:DMrun()
else
    be:MDLsetDMGTurn(0)
end
