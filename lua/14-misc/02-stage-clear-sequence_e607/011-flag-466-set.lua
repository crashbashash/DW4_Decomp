mswk67124 = "TALKFONT05/font00/I<43>"
mswk67125 = "TALKFONT05/font00/I<44>"
mswk67126 = "TALKFONT05/font00/I<45>"
mswk67127 = "TALKFONT05/font00/I<46>"
mswk67128 = "TALKFONT05/font00/I<47>"
mswk67129 = "TALKFONT05/font00/I<48>"
mswk67130 = "TALKFONT05/font00/I<49>"
local local_0 = function()
    be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
    be:DMsetSD("PLAYER", nil, -1, "OFCTRL")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:DMsetSD("MODELCTRL", "i_stpnl00", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_stpnl01", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_stpnl02", -1, "SQ_CLOSEWN")
    be:DMsetSD("MODELCTRL", "i_stpnl03", -1, "SQ_CLOSEWN")
    be:DMsetSD("MODELCTRL", "i_stpnl04", -1, "SQ_CLOSEWN")
end
local generatePlayer = function()
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "!=0")
    local local_0
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
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
    be:DMsetSD("ENEMY", nil, -1, "ONCTRL")
    be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
end
if be:FLGisOn(466) == 0 then
    be:FLGset(466, 1)
elseif be:FLGisOn(466) == 1 then
    local local_2 = be:COUNTERget(7) + 1
    be:COUNTERset(7, local_2)
    be:DMsetSD("PLAYER", nil, -1, "OFCTRL", 180)
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Bridge", 180)
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    local local_3
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            local maxMp = be:SYSctlPlayer("MP", "GETMMP", playerIndex, 0)
            be:DMsetSD("GAMERAM", nil, 0, "ADDMP", "I<" .. playerIndex .. ">/I<" .. maxMp .. ">")
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
    generatePlayer()
    be:DMrun()
end
