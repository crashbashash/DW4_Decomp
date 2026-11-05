be:MDLsetDMGTurn(0)
if be:MDLgetHp() > 0 then
    be:MDLsetSeq("SQ_SWON")
    be:MDLaddHp(-100)
end
for local_2 = 0, 3 do
    if be:SYSisJoinPlayer(local_2) == 1 then
        local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
    end
end
if be:FLGisOn(38) == 0 and local_1 ~= 0 then
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("PLAYER", nil, -1, "SQ_WAIT", 0)
    be:sd("HITLANDMODEL", "hitlift01z01", 0, "OFFHIT")
    be:DMchkSD("MODELCTRL", "g_lever01z01", 0, "ISSEQNAME", "SQ_SWON", "==0")
    be:DMchkSD("MODELCTRL", "g_lever01z01", 0, "ISSEQNAME", "SQ_SWON", "!=0")
    be:DMsetSD("MODELCTRL", "g_lift01z01", 0, "SQ_SWON", 20)
    be:sd("GENERATER", nil, -1, "START", "GBOX-01")
    be:FLGset(38, 1)
    if be:FLGisOn(506) == 0 then
        be:sd("ENEMY", nil, -1, "ONFREEZE")
        be:DMsetSD("PLAYER", nil, -1, "ONFREEZE")
        be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
        be:FLGset(506, 1)
        be:DMsetSD("CAMERA", nil, -1, "SHAKE", "37/F<0.3>/F<3.0>/F<60.0>", 20)
        be:DMsetSD("MODELCTRL", "i_stpnl00", -1, "SQ_CLOSE", 50)
        be:DMsetSD("MODELCTRL", "i_stpnl01", -1, "SQ_CLOSE", 50)
        be:DMsetSD("MODELCTRL", "i_stpnl02", -1, "SQ_CLOSEWN", 50)
        be:DMsetSD("MODELCTRL", "i_stpnl03", -1, "SQ_CLOSEWN", 50)
        be:DMsetSD("MODELCTRL", "i_stpnl04", -1, "SQ_CLOSEWN", 50)
        mswk67040 = "TALKFONT05/font00/I<20>"
        be:DMchkSD("MODELCTRL", "i_stpnl00", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_stpnl00", 0, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN")
        be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67040)
        be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "==0")
        be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET", 2)
        be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 2)
        be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
        be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
        be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
        be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_stpnl00", 0, "GENERATE", "SQ_OPEN")
        for local_3 = 0, 3 do
            if be:SYSisJoinPlayer(local_3) == 1 then
                if local_3 == 0 then
                    be:DMsetSD("MODELCTRL", "i_stpnl01", 0, "GENERATE", "V<-260,-160,0>/SQ_OPEN")
                    be:DMsetSD("MODELCTRL", "i_stpnl02", 0, "GENERATE", "V<-260,-160,0>/" .. be:SYSgetPlayerName(local_3))
                    be:DMsetSD("MODELCTRL", "i_stpnl03", 0, "GENERATE", "V<-260,-160,0>/SQ_OPENWN")
                    be:DMsetSD("MODELCTRL", "i_stpnl04", 0, "GENERATE", "V<-260,-160,0>/SQ_OPENWN")
                elseif local_3 == 1 then
                    be:DMsetSD("MODELCTRL", "i_stpnl01", 1, "GENERATE", "V<-110,-160,0>/SQ_OPEN")
                    be:DMsetSD("MODELCTRL", "i_stpnl02", 1, "GENERATE", "V<-110,-160,0>/" .. be:SYSgetPlayerName(local_3))
                    be:DMsetSD("MODELCTRL", "i_stpnl03", 1, "GENERATE", "V<-110,-160,0>/SQ_OPENWN")
                    be:DMsetSD("MODELCTRL", "i_stpnl04", 1, "GENERATE", "V<-110,-160,0>/SQ_OPENWN")
                elseif local_3 == 2 then
                    be:DMsetSD("MODELCTRL", "i_stpnl01", 2, "GENERATE", "V<40,-160,0>/SQ_OPEN")
                    be:DMsetSD("MODELCTRL", "i_stpnl02", 2, "GENERATE", "V<40,-160,0>/" .. be:SYSgetPlayerName(local_3))
                    be:DMsetSD("MODELCTRL", "i_stpnl03", 2, "GENERATE", "V<40,-160,0>/SQ_OPENWN")
                    be:DMsetSD("MODELCTRL", "i_stpnl04", 2, "GENERATE", "V<40,-160,0>/SQ_OPENWN")
                elseif local_3 == 3 then
                    be:DMsetSD("MODELCTRL", "i_stpnl01", 3, "GENERATE", "V<190,-160,0>/SQ_OPEN")
                    be:DMsetSD("MODELCTRL", "i_stpnl02", 3, "GENERATE", "V<190,-160,0>/" .. be:SYSgetPlayerName(local_3))
                    be:DMsetSD("MODELCTRL", "i_stpnl03", 3, "GENERATE", "V<190,-160,0>/SQ_OPENWN")
                    be:DMsetSD("MODELCTRL", "i_stpnl04", 3, "GENERATE", "V<190,-160,0>/SQ_OPENWN")
                end
            end
        end
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET")
        be:DMsetSD("ENEMY", nil, -1, "OFFREEZE")
        be:DMsetSD("PLAYER", nil, -1, "OFFREEZE")
    end
    be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
    be:DMrun()
end
