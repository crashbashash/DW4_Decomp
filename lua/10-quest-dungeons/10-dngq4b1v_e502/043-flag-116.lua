if be:MATisAllPlayer() ~= 1 and be:FLGisOn(116) ~= 1 then
    if be:DMgetCount() == -1 then
        be:sd("SUBWND", nil, -1, "REMOVE")
        be:DMchkSD("SUBWND", nil, -1, "ISRUN", "!=0")
    end
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN")
    be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "TALKFONT01/font00/CENTER")
    g_talk = "mess"
    g_page = 0
    g_messPlayerNo = 0
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT", 15)
    funcOneMessage(mswk61068)
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
    be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT", 15)
    be:DMsetSD("PLAYER", nil, -1, "ONCTRL", 15)
    be:DMsetSD("ENEMY", nil, -1, "ONCTRL", 15)
    be:DMrun()
    be:FLGset(116, 1)
    be:MATsetRun(0)
end
