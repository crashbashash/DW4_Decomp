be:sd("NDMWPANEL", nil, -1, "NOGATEDISK", "I<1>")
be:FLGset(466, 0)
be:FLGset(467, 0)
be:FLGset(468, 0)
be:FLGset(514, 0)
if be:FLGisOn(503) == 0 and be:DMgetCount() == 0 then
    g_messPlayerNo = 0
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:FLGset(503, 1)
    be:sd("PLAYER", nil, -1, "OFCTRL")
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 then
            be:DMsetSD("PLAYER", be:SYSgetPlayerName(local_2), local_2, "SQ_ENTR", local_1)
            local_1 = local_1 + 20
        end
    end
    mswk67080 = "TALKFONT05/font00/I<5>"
    be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "ENABLE", local_1 + 60)
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN", local_1 + 60)
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67080)
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67081 = "TALKFONT05/font00/I<6>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67081)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67082 = "TALKFONT05/font00/I<7>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67082)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67083 = "TALKFONT05/font00/I<8>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67083)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67084 = "TALKFONT05/font00/I<9>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67084)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67085 = "TALKFONT05/font00/I<10>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67085)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67086 = "TALKFONT05/font00/I<11>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67086)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67087 = "TALKFONT05/font00/I<12>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67087)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67088 = "TALKFONT05/font00/I<13>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67088)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67089 = "TALKFONT05/font00/I<14>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67089)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67090 = "TALKFONT05/font00/I<15>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67090)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    if be:FLGisOn(382) == 0 then
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-a00", 10)
        be:DMsetSD("ENEMY", nil, -1, "OFCTRL", 15)
    elseif be:FLGisOn(382) == 1 then
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-b00", 10)
        be:DMsetSD("ENEMY", nil, -1, "OFCTRL", 15)
    end
    mswk67091 = "TALKFONT05/font00/I<16>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67091)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "!=0")
    be:DMsetSD("MODELCTRL", "i_stpnl00", 0, "SQ_OPEN")
    for local_3 = 0, 3 do
        if be:SYSisJoinPlayer(local_3) == 1 then
            be:DMsetSD("MODELCTRL", "i_stpnl01", local_3, "SQ_OPEN")
            be:DMsetSD("MODELCTRL", "i_stpnl02", local_3, be:SYSgetPlayerName(local_3))
            be:DMsetSD("MODELCTRL", "i_stpnl03", local_3, "SQ_OPENWN")
            be:DMsetSD("MODELCTRL", "i_stpnl04", local_3, "SQ_OPENWN")
        end
    end
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
    be:DMsetSD("ENEMY", nil, -1, "ONCTRL", 10)
    be:DMsetSD("PLAYER", nil, -1, "ONCTRL", 10)
    be:DMsetSD("MATCTRL", nil, -1, "RESTART")
    be:DMrun()
end
g_gobuMode = 0
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
