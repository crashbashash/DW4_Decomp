for local_2 = 0, 3 do
    if be:SYSisJoinPlayer(local_2) == 1 then
        local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
    end
end
if local_1 == 0 then
    return nil, 0
end
be:sd("MODELCTRL", nil, -1, "OFCTRL")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossafter")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("MODELCTRL", "e_ldknight", 0, "MOVETRANS", "V<660,10,-680>/V<0,0,0>")
be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<670,10,-610>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<650,10,-610>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<690,10,-620>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<630,10,-620>/V<0,180,0>")
be:DMsetSD("SOUND", nil, -1, "PLAY", "BT_WIN03", 300)
be:DMsetSD("PLAYER", nil, -1, "SQ_ENJOY", 340)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
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
funcOneMessage(mswk61094)
be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossdoor")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("MODELCTRL", "g_d4door", 21, "SQ_SWON", 20)
be:DMsetSD("HITLANDMODEL", "doorwall22", 0, "OFFHIT", 35)
be:DMsetSD("MODELCTRL", "g_d4door", 22, "SQ_SWON", 20)
be:DMsetSD("HITLANDMODEL", "doorwall23", 0, "OFFHIT", 35)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_THEME", 60)
be:DMrun()
be:FLGset(208, 1)
be:FLGset(448, 1)
