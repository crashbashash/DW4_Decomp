for local_2 = 0, 3 do
    if be:SYSisJoinPlayer(local_2) == 1 then
        local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
    end
end
if local_1 == 0 then
    return nil, 0
end
be:sd("MODELCTRL", "i_timenm0", 0, "SQ_BLINK")
be:sd("MODELCTRL", "i_timenm0", 0, "SQ_STOP", 60)
be:sd("MODELCTRL", nil, -1, "OFCTRL")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossafter")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("MODELCTRL", "e_mammos", 0, "MOVETRANS", "V<-60,10,-560>/V<0,0,0>")
be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-50,10,-490>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-70,10,-490>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-30,10,-500>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-90,10,-500>/V<0,180,0>")
be:DMsetSD("SOUND", nil, -1, "PLAY", "BT_WIN03", 200)
be:DMsetSD("PLAYER", nil, -1, "SQ_ENJOY", 240)
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
funcOneMessage(mswk61002)
be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossdoor")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("MODELCTRL", "g_d1door", 8, "SQ_SWON", 20)
be:DMsetSD("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 35)
be:DMsetSD("MODELCTRL", "g_d1door", 9, "SQ_SWON", 20)
be:DMsetSD("HITLANDMODEL", "doorwall10", 0, "OFFHIT", 35)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_THEME", 60)
be:DMrun()
be:FLGset(115, 1)
be:FLGset(384, 1)
be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
be:FLGset(131, 1)
be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
be:FLGset(132, 1)
