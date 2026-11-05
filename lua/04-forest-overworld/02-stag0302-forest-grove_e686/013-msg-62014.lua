be:MDLsetDMGTurn(0)
if be:FLGisOn(56) == 0 then
    if be:DMgetCount() == 0 then
        g_messPlayerNo = be:BLTgetShootRamNo()
        be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
        be:sd("ENEMY", nil, -1, "OFCTRL")
        be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
        be:DMchkSD("PLAYER", local_1, local_0, "ISSEQNAME", "SQ_WAIT", "==0")
        be:sd("PLAYER", nil, -1, "OFCTRL")
        funcOpenMessage("mess")
        mswk62014 = "TALKFONT01/font00/I<15>"
        funcOneMessage(mswk62014)
        funcCloseMessage("mess")
        be:DMrun()
    else
    end
end
if be:FLGisOn(56) == 1 and be:MDLgetHp() > 0 and be:DMgetCount() == 0 then
    g_messPlayerNo = be:BLTgetShootRamNo()
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:DMchkSD("PLAYER", local_1, local_0, "ISSEQNAME", "SQ_WAIT", "==0")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:DMsetSD("MODELCTRL", "g_consolez03", 0, "SQ_SWON")
    funcOpenMessage("mess")
    mswk64008 = "TALKFONT01/font00/I<16>"
    funcOneMessage(mswk64008)
    funcCloseMessage("mess")
    be:DMsetSD("MODELCTRL", "g_breakdoorz03", 0, "SQ_SWON")
    be:DMrun()
end
