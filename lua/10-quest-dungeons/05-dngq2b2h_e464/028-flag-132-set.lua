if be:FLGisOn(137) ~= 1 and g_mummyStock > 0 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-13", 1)
    g_mummyStock = g_mummyStock + -1
else
    be:FLGset(132, 1)
end
local local_0
local total = 0
for counterNo = 3, 6 do
    total = total + be:COUNTERget(counterNo)
end
if total >= g_enemyAmount then
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
