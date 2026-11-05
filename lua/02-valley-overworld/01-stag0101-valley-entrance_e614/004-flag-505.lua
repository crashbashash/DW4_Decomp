for local_2 = 0, 3 do
    if be:SYSisJoinPlayer(local_2) == 1 then
        local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
    end
end
if be:FLGisOn(505) == 0 and local_1 ~= 0 then
    if be:DMgetCount() == -1 then
        be:sd("SUBWND", nil, -1, "REMOVE")
        be:DMchkSD("SUBWND", nil, -1, "ISRUN", "!=0")
    end
    g_spdemocheck = 1
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:FLGset(505, 1)
    be:DMsetSD("MODELCTRL", "i_stpnl00", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_stpnl01", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_stpnl02", -1, "SQ_CLOSEWN")
    be:DMsetSD("MODELCTRL", "i_stpnl03", -1, "SQ_CLOSEWN")
    be:DMsetSD("MODELCTRL", "i_stpnl04", -1, "SQ_CLOSEWN")
    be:DMchkSD("MODELCTRL", "i_stpnl00", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_stpnl00", 0, "ISRUN", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "camsp0401")
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    mswk67031 = "TALKFONT05/font00/I<21>"
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN")
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67031)
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67032 = "TALKFONT05/font00/I<22>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67032)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "camsp0402")
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    mswk67033 = "TALKFONT05/font00/I<23>"
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN")
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67033)
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67034 = "TALKFONT05/font00/I<24>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67034)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "camsp0403")
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    mswk67035 = "TALKFONT05/font00/I<25>"
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN")
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67035)
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67036 = "TALKFONT05/font00/I<26>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67036)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
    for local_4 = 0, 3 do
        if be:SYSisJoinPlayer(local_4) == 0 then
            be:DMsetSD("MODELCTRL", "g_sbutton", local_4, "SQ_ONLOOP")
        end
    end
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "camsp0404")
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    mswk67037 = "TALKFONT05/font00/I<27>"
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN")
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67037)
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "!=0")
    for local_4 = 0, 3 do
        if be:SYSisJoinPlayer(local_4) == 1 then
            be:DMsetSD("MODELCTRL", "g_sbutton", local_4, "SQ_SWON", local_2)
            local_2 = local_2 + 20
            local_3 = local_4
        end
    end
    be:DMchkSD("MODELCTRL", "g_sbutton", local_3, "ISSEQNAME", "SQ_SWON", "==0")
    be:DMchkSD("MODELCTRL", "g_sbutton", local_3, "ISSEQNAME", "SQ_SWON", "!=0")
    be:DMsetSD("MODELCTRL", "g_gobgatez01", 0, "SQ_SWON", 30)
    be:DMchkSD("MODELCTRL", "g_gobgatez01", 0, "ISSEQNAME", "SQ_SWON", "==0")
    be:DMchkSD("MODELCTRL", "g_gobgatez01", 0, "ISSEQNAME", "SQ_SWON", "!=0")
    mswk67038 = "TALKFONT05/font00/I<28>"
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN")
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67038)
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67039 = "TALKFONT05/font00/I<29>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67039)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "!=0")
    be:DMsetSD("MODELCTRL", "g_sbutton", -1, "SQ_POWEROF")
    be:DMsetSD("MODELCTRL", "g_gobgatez01", 0, "SQ_SWOF")
    be:DMsetSD("MODELCTRL", "i_stpnl00", 0, "GENERATE", "SQ_OPEN")
    for local_5 = 0, 3 do
        if be:SYSisJoinPlayer(local_5) == 1 then
            if local_5 == 0 then
                be:DMsetSD("MODELCTRL", "i_stpnl01", 0, "GENERATE", "V<-260,-160,0>/SQ_OPEN")
                be:DMsetSD("MODELCTRL", "i_stpnl02", 0, "GENERATE", "V<-260,-160,0>/" .. be:SYSgetPlayerName(local_5))
                be:DMsetSD("MODELCTRL", "i_stpnl03", 0, "GENERATE", "V<-260,-160,0>/SQ_OPENWN")
                be:DMsetSD("MODELCTRL", "i_stpnl04", 0, "GENERATE", "V<-260,-160,0>/SQ_OPENWN")
            elseif local_5 == 1 then
                be:DMsetSD("MODELCTRL", "i_stpnl01", 1, "GENERATE", "V<-110,-160,0>/SQ_OPEN")
                be:DMsetSD("MODELCTRL", "i_stpnl02", 1, "GENERATE", "V<-110,-160,0>/" .. be:SYSgetPlayerName(local_5))
                be:DMsetSD("MODELCTRL", "i_stpnl03", 1, "GENERATE", "V<-110,-160,0>/SQ_OPENWN")
                be:DMsetSD("MODELCTRL", "i_stpnl04", 1, "GENERATE", "V<-110,-160,0>/SQ_OPENWN")
            elseif local_5 == 2 then
                be:DMsetSD("MODELCTRL", "i_stpnl01", 2, "GENERATE", "V<40,-160,0>/SQ_OPEN")
                be:DMsetSD("MODELCTRL", "i_stpnl02", 2, "GENERATE", "V<40,-160,0>/" .. be:SYSgetPlayerName(local_5))
                be:DMsetSD("MODELCTRL", "i_stpnl03", 2, "GENERATE", "V<40,-160,0>/SQ_OPENWN")
                be:DMsetSD("MODELCTRL", "i_stpnl04", 2, "GENERATE", "V<40,-160,0>/SQ_OPENWN")
            elseif local_5 == 3 then
                be:DMsetSD("MODELCTRL", "i_stpnl01", 3, "GENERATE", "V<190,-160,0>/SQ_OPEN")
                be:DMsetSD("MODELCTRL", "i_stpnl02", 3, "GENERATE", "V<190,-160,0>/" .. be:SYSgetPlayerName(local_5))
                be:DMsetSD("MODELCTRL", "i_stpnl03", 3, "GENERATE", "V<190,-160,0>/SQ_OPENWN")
                be:DMsetSD("MODELCTRL", "i_stpnl04", 3, "GENERATE", "V<190,-160,0>/SQ_OPENWN")
            end
        end
    end
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET")
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
    be:DMsetSD("ENEMY", nil, -1, "ONCTRL")
    be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
    be:DMrun()
end
