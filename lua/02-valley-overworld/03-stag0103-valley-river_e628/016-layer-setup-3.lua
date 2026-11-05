be:sd("PLAYER", nil, -1, "SQ_FALL")
be:sd("NDMWPANEL", nil, -1, "NOHEALING", "I<1>")
be:sd("NDMWPANEL", nil, -1, "NOCURELING", "I<1>")
be:sd("NDMWPANEL", nil, -1, "NOPARAUP", "I<1>")
be:sd("NDMWPANEL", nil, -1, "NOGATEDISK", "I<1>")
be:FLGset(481, 0)
be:FLGset(482, 0)
be:FLGset(483, 0)
be:FLGset(484, 0)
be:FLGset(485, 0)
be:FLGset(486, 0)
be:FLGset(487, 0)
be:FLGset(488, 0)
be:FLGset(489, 0)
g_pCount = 0
for local_1 = 0, 3 do
    if be:SYSisJoinPlayer(local_1) == 1 then
        g_pCount = g_pCount + 1
    end
end
if g_pCount == 1 then
    g_meta = 50
    g_dmgnum = 5
    g_hpnum1 = 75
    g_hpnum2 = 50
    g_hpnum3 = 25
    g_hpnum4 = 0
elseif g_pCount == 2 then
    g_meta = 50
    g_dmgnum = 4
    g_hpnum1 = 76
    g_hpnum2 = 52
    g_hpnum3 = 28
    g_hpnum4 = 0
elseif g_pCount == 3 then
    g_meta = 75
    g_dmgnum = 3
    g_hpnum1 = 76
    g_hpnum2 = 52
    g_hpnum3 = 28
    g_hpnum4 = 1
elseif g_pCount == 4 then
    g_meta = 100
    g_dmgnum = 2
    g_hpnum1 = 74
    g_hpnum2 = 50
    g_hpnum3 = 24
    g_hpnum4 = 0
end
be:sd("METERCTRL", "boathp", 0, "SETPERCENT", "F<" .. g_meta .. ">")
g_boathp = 100
be:sd("PLAYER", nil, -1, "OFCTRL")
be:sd("ENEMY", nil, -1, "OFCTRL")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLIN60", "==0")
if be:SYSisJoinPlayer(0) == 1 then
    be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<575,15,395>/V<0,-90,0>")
end
if be:SYSisJoinPlayer(1) == 1 then
    be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<585,15,400>/V<0,-90,0>")
end
if be:SYSisJoinPlayer(2) == 1 then
    be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<585,15,388>/V<0,-90,0>")
end
if be:SYSisJoinPlayer(3) == 1 then
    be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<595,15,395>/V<0,-90,0>")
end
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLIN60", "!=0")
be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "ENABLE")
mswk62000 = "TALKFONT01/font00/I<0>"
mswk62001 = "TALKFONT01/font00/I<1>"
mswk62010 = "TALKFONT01/font00/I<2>"
mswk62011 = "TALKFONT01/font00/I<3>"
g_messPlayerNo = 0
funcOpenMessage("mess")
funcOneMessage(mswk62000)
funcOneMessage(mswk62001)
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
funcCloseMessage("mess", "demo")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "==0")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "nume1")
if be:FLGisOn(89) == 1 and be:MDLisLive("n_digilfm", 0) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 0, "GENERATE", "V<60,15,413.5>/V<0,180,0>/SQ_HELP")
end
be:DMchkSD("MODELCTRL", "n_digilfm", 0, "ISRUN", "==0")
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30")
funcOpenMessage("mess")
funcOneMessage(mswk62010)
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
funcCloseMessage("mess", "demo")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "==0")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "!=0")
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>")
if be:SYSisJoinPlayer(0) == 1 then
    be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<575,15,395>/V<0,-90,0>")
end
if be:SYSisJoinPlayer(1) == 1 then
    be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<585,15,400>/V<0,-90,0>")
end
if be:SYSisJoinPlayer(2) == 1 then
    be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<585,15,388>/V<0,-90,0>")
end
if be:SYSisJoinPlayer(3) == 1 then
    be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<595,15,395>/V<0,-90,0>")
end
if be:FLGisOn(89) == 1 and be:MDLisLive("n_digilfm", 0) == 1 then
    be:DMsetSD("MODELCTRL", "n_digilfm", 0, "SQ_ERAS", 40)
end
funcOpenMessage("mess")
funcOneMessage(mswk62011)
funcCloseMessage("mess")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "!=0")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
if not g_delayTime then
    g_delayTime = 0
end
be:DMsetSD("MODELCTRL", "i_stpnl00", 0, "SQ_OPEN", g_delayTime)
be:DMsetSD("MODELCTRL", "i_stpnlsp04", 0, "SQ_OPEN", g_delayTime)
be:DMsetSD("MODELCTRL", "i_stpnlsp05", 0, "SQ_OPEN", g_delayTime)
for local_2 = 0, 3 do
    if be:SYSisJoinPlayer(local_2) == 1 then
        if local_2 == 0 then
            be:DMsetSD("MODELCTRL", "i_stpnlsp01", 0, "SQ_OPEN", g_delayTime)
            be:DMsetSD("MODELCTRL", "i_stpnl02", 0, be:SYSgetPlayerName(local_2), g_delayTime)
            be:DMsetSD("MODELCTRL", "i_stpnlsp02", 0, "SQ_OPENWN", g_delayTime)
            be:DMsetSD("MODELCTRL", "i_stpnlsp03", 0, "SQ_OPENWN", g_delayTime)
            be:DMsetSD("MODELCTRL", "i_stpnl05", 0, "SQ_WAIT", g_delayTime)
        elseif local_2 == 1 then
            be:DMsetSD("MODELCTRL", "i_stpnlsp01", 1, "SQ_OPEN", g_delayTime + 5)
            be:DMsetSD("MODELCTRL", "i_stpnl02", 1, be:SYSgetPlayerName(local_2), g_delayTime + 5)
            be:DMsetSD("MODELCTRL", "i_stpnlsp02", 1, "SQ_OPENWN", g_delayTime + 5)
            be:DMsetSD("MODELCTRL", "i_stpnlsp03", 1, "SQ_OPENWN", g_delayTime + 5)
            be:DMsetSD("MODELCTRL", "i_stpnl05", 1, "SQ_WAIT", g_delayTime + 5)
        elseif local_2 == 2 then
            be:DMsetSD("MODELCTRL", "i_stpnlsp01", 2, "SQ_OPEN", g_delayTime + 10)
            be:DMsetSD("MODELCTRL", "i_stpnl02", 2, be:SYSgetPlayerName(local_2), g_delayTime + 10)
            be:DMsetSD("MODELCTRL", "i_stpnlsp02", 2, "SQ_OPENWN", g_delayTime + 10)
            be:DMsetSD("MODELCTRL", "i_stpnlsp03", 2, "SQ_OPENWN", g_delayTime + 10)
            be:DMsetSD("MODELCTRL", "i_stpnl05", 2, "SQ_WAIT", g_delayTime + 10)
        elseif local_2 == 3 then
            be:DMsetSD("MODELCTRL", "i_stpnlsp01", 3, "SQ_OPEN", g_delayTime + 15)
            be:DMsetSD("MODELCTRL", "i_stpnl02", 3, be:SYSgetPlayerName(local_2), g_delayTime + 15)
            be:DMsetSD("MODELCTRL", "i_stpnlsp02", 3, "SQ_OPENWN", g_delayTime + 15)
            be:DMsetSD("MODELCTRL", "i_stpnlsp03", 3, "SQ_OPENWN", g_delayTime + 15)
            be:DMsetSD("MODELCTRL", "i_stpnl05", 3, "SQ_WAIT", g_delayTime + 15)
        end
    end
end
be:DMsetSD("MODELCTRL", "i_digilfbase", 0, "SQ_OPEN", g_delayTime)
if be:FLGisOn(89) == 0 then
    be:DMsetSD("MODELCTRL", "i_digilfcount", 0, "SQ_OPENOF", g_delayTime + 5)
else
    be:DMsetSD("MODELCTRL", "i_digilfcount", 0, "SQ_OPENON", g_delayTime + 5)
end
if be:FLGisOn(90) == 0 then
    be:DMsetSD("MODELCTRL", "i_digilfcount", 2, "SQ_OPENOF", g_delayTime + 15)
else
    be:DMsetSD("MODELCTRL", "i_digilfcount", 2, "SQ_OPENON", g_delayTime + 15)
end
if be:FLGisOn(91) == 0 then
    be:DMsetSD("MODELCTRL", "i_digilfcount", 1, "SQ_OPENOF", g_delayTime + 10)
else
    be:DMsetSD("MODELCTRL", "i_digilfcount", 1, "SQ_OPENON", g_delayTime + 10)
end
if be:FLGisOn(92) == 0 then
    be:DMsetSD("MODELCTRL", "i_digilfcount", 3, "SQ_OPENOF", g_delayTime + 20)
else
    be:DMsetSD("MODELCTRL", "i_digilfcount", 3, "SQ_OPENON", g_delayTime + 20)
end
if be:FLGisOn(93) == 0 then
    be:DMsetSD("MODELCTRL", "i_digilfcount", 4, "SQ_OPENOF", g_delayTime + 25)
else
    be:DMsetSD("MODELCTRL", "i_digilfcount", 4, "SQ_OPENON", g_delayTime + 25)
end
if be:FLGisOn(94) == 0 then
    be:DMsetSD("MODELCTRL", "i_digilfcount", 5, "SQ_OPENOF", g_delayTime + 30)
else
    be:DMsetSD("MODELCTRL", "i_digilfcount", 5, "SQ_OPENON", g_delayTime + 30)
end
if be:FLGisOn(95) == 0 then
    be:DMsetSD("MODELCTRL", "i_digilfcount", 6, "SQ_OPENOF", g_delayTime + 35)
else
    be:DMsetSD("MODELCTRL", "i_digilfcount", 6, "SQ_OPENON", g_delayTime + 35)
end
if be:FLGisOn(96) == 0 then
    be:DMsetSD("MODELCTRL", "i_digilfcount", 7, "SQ_OPENOF", g_delayTime + 40)
else
    be:DMsetSD("MODELCTRL", "i_digilfcount", 7, "SQ_OPENON", g_delayTime + 40)
end
if be:FLGisOn(97) == 0 then
    be:DMsetSD("MODELCTRL", "i_digilfcount", 8, "SQ_OPENOF", g_delayTime + 45)
else
    be:DMsetSD("MODELCTRL", "i_digilfcount", 8, "SQ_OPENON", g_delayTime + 45)
end
if be:FLGisOn(98) == 0 then
    be:DMsetSD("MODELCTRL", "i_digilfcount", 9, "SQ_OPENOF", g_delayTime + 50)
else
    be:DMsetSD("MODELCTRL", "i_digilfcount", 9, "SQ_OPENON", g_delayTime + 50)
end
be:DMsetSD("MODELCTRL", "r_boatz01", 0, "SQ_GO", 20)
be:DMsetSD("MODELCTRL", "g_boatz01", 0, "SQ_START", 20)
be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_SPE01")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 120)
be:DMrun()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 30)
