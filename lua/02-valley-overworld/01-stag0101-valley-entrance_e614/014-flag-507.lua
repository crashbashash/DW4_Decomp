g_GateStage = "stag0101"
g_GatePos = 3
for local_7 = 0, 3 do
    if be:SYSisJoinPlayer(local_7) == 1 then
        if be:MDLisLive(be:SYSgetPlayerName(local_7), local_7) == 1 then
            local_4 = local_4 + 1
        end
        if be:MATgetPlayerMatStat(local_7) == 0 then
            local_3 = local_3 + 1
        elseif be:MATgetPlayerMatStat(local_7) == 1 then
            local_2 = local_2 + 1
        elseif be:MATgetPlayerMatStat(local_7) == 2 then
            local_0 = local_0 + 1
        elseif be:MATgetPlayerMatStat(local_7) == 3 then
            local_1 = local_1 + 1
        end
    end
end
if local_0 + local_1 == local_4 then
    be:sd("MODELCTRL", "g_security", 0, "SQ_SWON")
    g_GateOn = 1
    for local_7 = 0, 3 do
        if be:SYSisJoinPlayer(local_7) == 1 then
            local_6 = local_6 + be:SYSctlPlayer("HP", "GETHP", local_7, 0)
        end
    end
    if be:FLGisOn(507) == 0 and local_6 ~= 0 then
        if be:DMgetCount() == -1 then
            be:sd("SUBWND", nil, -1, "REMOVE")
            be:DMchkSD("SUBWND", nil, -1, "ISRUN", "!=0")
        end
        be:sd("ENEMY", nil, -1, "OFCTRL")
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
        be:FLGset(507, 1)
        be:DMsetSD("MODELCTRL", "i_stpnl00", -1, "SQ_CLOSE")
        be:DMsetSD("MODELCTRL", "i_stpnl01", -1, "SQ_CLOSE")
        be:DMsetSD("MODELCTRL", "i_stpnl02", -1, "SQ_CLOSEWN")
        be:DMsetSD("MODELCTRL", "i_stpnl03", -1, "SQ_CLOSEWN")
        be:DMsetSD("MODELCTRL", "i_stpnl04", -1, "SQ_CLOSEWN")
        mswk67041 = "TALKFONT05/font00/I<30>"
        be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN")
        be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67041)
        be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "==0")
        be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
        be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
        be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
        be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
        mswk67042 = "TALKFONT05/font00/I<31>"
        be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67042)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
        be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
        be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
        be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
        be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
        be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_stpnl00", 0, "GENERATE", "SQ_OPEN")
        for local_9 = 0, 3 do
            if be:SYSisJoinPlayer(local_9) == 1 then
                if local_9 == 0 then
                    be:DMsetSD("MODELCTRL", "i_stpnl01", 0, "GENERATE", "V<-260,-160,0>/SQ_OPEN")
                    be:DMsetSD("MODELCTRL", "i_stpnl02", 0, "GENERATE", "V<-260,-160,0>/" .. be:SYSgetPlayerName(local_9))
                    be:DMsetSD("MODELCTRL", "i_stpnl03", 0, "GENERATE", "V<-260,-160,0>/SQ_OPENWN")
                    be:DMsetSD("MODELCTRL", "i_stpnl04", 0, "GENERATE", "V<-260,-160,0>/SQ_OPENWN")
                elseif local_9 == 1 then
                    be:DMsetSD("MODELCTRL", "i_stpnl01", 1, "GENERATE", "V<-110,-160,0>/SQ_OPEN")
                    be:DMsetSD("MODELCTRL", "i_stpnl02", 1, "GENERATE", "V<-110,-160,0>/" .. be:SYSgetPlayerName(local_9))
                    be:DMsetSD("MODELCTRL", "i_stpnl03", 1, "GENERATE", "V<-110,-160,0>/SQ_OPENWN")
                    be:DMsetSD("MODELCTRL", "i_stpnl04", 1, "GENERATE", "V<-110,-160,0>/SQ_OPENWN")
                elseif local_9 == 2 then
                    be:DMsetSD("MODELCTRL", "i_stpnl01", 2, "GENERATE", "V<40,-160,0>/SQ_OPEN")
                    be:DMsetSD("MODELCTRL", "i_stpnl02", 2, "GENERATE", "V<40,-160,0>/" .. be:SYSgetPlayerName(local_9))
                    be:DMsetSD("MODELCTRL", "i_stpnl03", 2, "GENERATE", "V<40,-160,0>/SQ_OPENWN")
                    be:DMsetSD("MODELCTRL", "i_stpnl04", 2, "GENERATE", "V<40,-160,0>/SQ_OPENWN")
                elseif local_9 == 3 then
                    be:DMsetSD("MODELCTRL", "i_stpnl01", 3, "GENERATE", "V<190,-160,0>/SQ_OPEN")
                    be:DMsetSD("MODELCTRL", "i_stpnl02", 3, "GENERATE", "V<190,-160,0>/" .. be:SYSgetPlayerName(local_9))
                    be:DMsetSD("MODELCTRL", "i_stpnl03", 3, "GENERATE", "V<190,-160,0>/SQ_OPENWN")
                    be:DMsetSD("MODELCTRL", "i_stpnl04", 3, "GENERATE", "V<190,-160,0>/SQ_OPENWN")
                end
            end
        end
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET")
        be:DMsetSD("ENEMY", nil, -1, "ONCTRL")
        be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
        be:DMrun()
    else
    end
end
be:sd("MODELCTRL", "g_security", 0, "SQ_SWOF")
g_GateOn = 0
