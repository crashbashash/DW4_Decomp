local count = 0
local count2 = 0
local count3 = 0
local count4 = 0
local count5 = 0
local local_5
local total = 0
g_GateStage = "stag0101"
g_GatePos = 3
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        if be:MDLisLive(be:SYSgetPlayerName(playerIndex), playerIndex) == 1 then
            count5 = count5 + 1
        end
        if be:MATgetPlayerMatStat(playerIndex) == 0 then
            count4 = count4 + 1
        elseif be:MATgetPlayerMatStat(playerIndex) == 1 then
            count3 = count3 + 1
        elseif be:MATgetPlayerMatStat(playerIndex) == 2 then
            count = count + 1
        elseif be:MATgetPlayerMatStat(playerIndex) == 3 then
            count2 = count2 + 1
        end
    end
end
if count + count2 == count5 then
    be:sd("MODELCTRL", "g_security", 0, "SQ_SWON")
    g_GateOn = 1
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            total = total + be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
        end
    end
    if be:FLGisOn(507) == 0 and total ~= 0 then
        if be:DMgetCount() == -1 then
            be:sd("SUBWND", nil, -1, "REMOVE")
            be:DMchkSD("SUBWND", nil, -1, "ISRUN", "!=0")
        end
        local local_7
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
        local local_8
        be:DMsetSD("MODELCTRL", "i_stpnl00", 0, "GENERATE", "SQ_OPEN")
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                if playerIndex == 0 then
                    be:DMsetSD("MODELCTRL", "i_stpnl01", 0, "GENERATE", "V<-260,-160,0>/SQ_OPEN")
                    be:DMsetSD("MODELCTRL", "i_stpnl02", 0, "GENERATE", "V<-260,-160,0>/" .. be:SYSgetPlayerName(playerIndex))
                    be:DMsetSD("MODELCTRL", "i_stpnl03", 0, "GENERATE", "V<-260,-160,0>/SQ_OPENWN")
                    be:DMsetSD("MODELCTRL", "i_stpnl04", 0, "GENERATE", "V<-260,-160,0>/SQ_OPENWN")
                elseif playerIndex == 1 then
                    be:DMsetSD("MODELCTRL", "i_stpnl01", 1, "GENERATE", "V<-110,-160,0>/SQ_OPEN")
                    be:DMsetSD("MODELCTRL", "i_stpnl02", 1, "GENERATE", "V<-110,-160,0>/" .. be:SYSgetPlayerName(playerIndex))
                    be:DMsetSD("MODELCTRL", "i_stpnl03", 1, "GENERATE", "V<-110,-160,0>/SQ_OPENWN")
                    be:DMsetSD("MODELCTRL", "i_stpnl04", 1, "GENERATE", "V<-110,-160,0>/SQ_OPENWN")
                elseif playerIndex == 2 then
                    be:DMsetSD("MODELCTRL", "i_stpnl01", 2, "GENERATE", "V<40,-160,0>/SQ_OPEN")
                    be:DMsetSD("MODELCTRL", "i_stpnl02", 2, "GENERATE", "V<40,-160,0>/" .. be:SYSgetPlayerName(playerIndex))
                    be:DMsetSD("MODELCTRL", "i_stpnl03", 2, "GENERATE", "V<40,-160,0>/SQ_OPENWN")
                    be:DMsetSD("MODELCTRL", "i_stpnl04", 2, "GENERATE", "V<40,-160,0>/SQ_OPENWN")
                elseif playerIndex == 3 then
                    be:DMsetSD("MODELCTRL", "i_stpnl01", 3, "GENERATE", "V<190,-160,0>/SQ_OPEN")
                    be:DMsetSD("MODELCTRL", "i_stpnl02", 3, "GENERATE", "V<190,-160,0>/" .. be:SYSgetPlayerName(playerIndex))
                    be:DMsetSD("MODELCTRL", "i_stpnl03", 3, "GENERATE", "V<190,-160,0>/SQ_OPENWN")
                    be:DMsetSD("MODELCTRL", "i_stpnl04", 3, "GENERATE", "V<190,-160,0>/SQ_OPENWN")
                end
            end
        end
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET")
        be:DMsetSD("ENEMY", nil, -1, "ONCTRL")
        be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
        be:DMrun()
    end
else
    be:sd("MODELCTRL", "g_security", 0, "SQ_SWOF")
    g_GateOn = 0
end
