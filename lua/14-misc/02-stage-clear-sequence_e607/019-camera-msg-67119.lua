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
be:DMsetSD("PLAYER", nil, -1, "OFCTRL", 180)
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "stageend", 220)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
local local_2
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        local maxMp = be:SYSctlPlayer("MP", "GETMMP", playerIndex, 0)
        be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "MOVETRANS", be:PLAYERgetDataStr(0, playerIndex, 0))
        be:DMsetSD("PLAYER", nil, playerIndex, "SQ_WAIT")
        be:DMsetSD("GAMERAM", nil, 0, "ADDMP", "I<" .. playerIndex .. ">/I<" .. maxMp .. ">")
    end
end
be:DMsetSD("PLAYER", nil, -1, "SQ_ENJOY", 10)
be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_COMMA", 80)
be:DMsetSD("MODELCTRL", "g_bush01z01", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "g_rock01z01", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "g_rock02z01", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "x_rock01z01", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "x_rock02z01", -1, "SQ_ERAS")
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30", 50)
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("MODELCTRL", "g_rock01z01", 1, "GENERATE", "V<-105,10,-20>/V<0,0,0>")
be:DMsetSD("MODELCTRL", "g_bush01z01", 2, "GENERATE", "V<-105,10,10>/V<0,0,0>")
be:DMsetSD("MODELCTRL", "g_rock01z01", 4, "GENERATE", "V<-105,10,20>/V<0,0,0>")
be:DMsetSD("MODELCTRL", "g_bush01z01", 5, "GENERATE", "V<-95,10,20>/V<0,0,0>")
be:DMsetSD("MODELCTRL", "g_bush01z01", 8, "GENERATE", "V<-75,10,-20>/V<0,0,0>")
be:DMsetSD("MODELCTRL", "g_rock01z01", 9, "GENERATE", "V<-65,10,-20>/V<0,0,0>")
be:DMsetSD("MODELCTRL", "g_bush01z01", 11, "GENERATE", "V<-65,10,-10>/V<0,0,0>")
be:DMsetSD("MODELCTRL", "g_rock01z01", 12, "GENERATE", "V<-65,10,20>/V<0,0,0>")
be:DMsetSD("MODELCTRL", "g_bush01z01", 14, "GENERATE", "V<5,10,-10>/V<0,0,0>")
be:DMsetSD("MODELCTRL", "g_bush01z01", 15, "GENERATE", "V<25,10,10>/V<0,0,0>")
if be:FLGisOn(382) == 0 then
    be:DMsetSD("GENERATER", nil, -1, "START", "GBOX-02")
elseif be:FLGisOn(382) == 1 then
    be:DMsetSD("GENERATER", nil, -1, "START", "GBOX-04")
end
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 30)
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLIN30", "==0")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLIN30", "!=0")
local_0()
mswk67119 = "TALKFONT05/font00/I<0>"
be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN")
be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67119)
be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "==0")
be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "==0")
be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET", 2)
be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 2)
be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
mswk67120 = "TALKFONT05/font00/I<1>"
be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67120)
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET", 2)
be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 2)
be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
mswk67121 = "TALKFONT05/font00/I<2>"
be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67121)
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET", 2)
be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 2)
be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
mswk67122 = "TALKFONT05/font00/I<3>"
be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67122)
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET", 2)
be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 2)
be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
mswk67123 = "TALKFONT05/font00/I<4>"
be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67123)
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET", 2)
be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 2)
be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
if be:FLGisOn(382) == 0 then
    if be:SYSgetPlayerNinzu() <= 2 then
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-a03")
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-a04")
    elseif be:SYSgetPlayerNinzu() >= 3 then
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-a05")
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-a06")
    end
elseif be:FLGisOn(382) == 1 then
    if be:SYSgetPlayerNinzu() <= 2 then
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-b03")
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-b04")
    elseif be:SYSgetPlayerNinzu() >= 3 then
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-b05")
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-b06")
    end
end
generatePlayer()
be:DMrun()
