be:sd("MODELCTRL", "g_d2door", 3, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
if be:FLGisOn(141) ~= 1 then
    for local_1 = 23, 29 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
be:FLGset(131, 1)
for local_2 = 3, 6 do
    local_1 = local_1 + be:COUNTERget(local_2)
end
if local_1 >= g_enemyAmount then
    if be:DMgetCount() == -1 then
        be:sd("SUBWND", nil, -1, "REMOVE")
        be:DMchkSD("SUBWND", nil, -1, "ISRUN", "!=0")
    end
    be:FLGset(144, 1)
    be:sd("MODELCTRL", "i_timenm0", 0, "SQ_BLINK")
    be:sd("MODELCTRL", nil, -1, "OFCTRL")
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
    funcOneMessage(mswk61007)
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
    be:DMsetSD("MODELCTRL", "i_timenm0", 0, "SQ_STOP", 60)
    be:DMrun()
end
