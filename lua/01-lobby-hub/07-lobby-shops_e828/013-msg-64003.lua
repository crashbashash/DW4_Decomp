be:MDLsetDMGTurn(0)
if be:FLGisOn(329) == 1 then
    if be:MDLgetHp() > 0 and be:DMgetCount() == 0 then
        g_messPlayerNo = be:BLTgetShootRamNo()
        be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:sd("ENEMY", nil, -1, "OFCTRL")
        funcOpenMessage("mess")
        mswk64003 = "TALKFONT01/font00/I<28>"
        funcOneMessage(mswk64003)
        funcCloseMessage("mess", "demo")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("MODELCTRL", "g_junkconsz05", 0, "SQ_SWOF")
        be:DMsetSD("HITLANDMODEL", "hitjunkconsz05", 0, "OFFHIT")
        be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 90)
        be:DMrun()
    else
    end
end
if be:FLGisOn(329) == 0 and be:DMgetCount() == 0 then
    g_messPlayerNo = be:BLTgetShootRamNo()
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    funcOpenMessage("mess")
    mswk64002 = "TALKFONT01/font00/I<29>"
    funcOneMessage(mswk64002)
    funcCloseMessage("mess")
    be:DMrun()
end
