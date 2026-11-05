mswk67124 = "TALKFONT05/font00/I<43>"
mswk67125 = "TALKFONT05/font00/I<44>"
mswk67126 = "TALKFONT05/font00/I<45>"
mswk67127 = "TALKFONT05/font00/I<46>"
mswk67128 = "TALKFONT05/font00/I<47>"
mswk67129 = "TALKFONT05/font00/I<48>"
mswk67130 = "TALKFONT05/font00/I<49>"
if be:FLGisOn(466) == 0 then
    be:FLGset(466, 1)
elseif be:FLGisOn(466) == 1 then
    be:COUNTERset(7, local_2)
    be:DMsetSD("PLAYER", nil, -1, "OFCTRL", 180)
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Bridge", 180)
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    for local_4 = 0, 3 do
        if be:SYSisJoinPlayer(local_4) == 1 then
            be:DMsetSD("GAMERAM", nil, 0, "ADDMP", "I<" .. local_4 .. ">/I<" .. local_7 .. ">")
        end
    end
    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT")
    be:DMsetSD("MODELCTRL", "g_hideliftz00", 0, "SQ_SWON", 30)
    be:DMsetSD("MODELCTRL", "g_cytelep1", 0, "SQ_POWERON")
    be:DMchkSD("MODELCTRL", "g_hideliftz00", 0, "ISSEQNAME", "SQ_SWON", "==0")
    be:DMchkSD("MODELCTRL", "g_hideliftz00", 0, "ISSEQNAME", "SQ_SWON", "!=0")
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 120)
    be:DMsetSD("HITLANDMODEL", "hithideliftz00", 0, "OFFHIT")
    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_COMMA", 170)
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN", 120)
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    local_0()
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67124)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67125)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    local_1()
    be:DMrun()
end
