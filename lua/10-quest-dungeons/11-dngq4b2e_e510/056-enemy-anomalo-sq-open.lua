local playerIndex
local total = 0
for playerIndex2 = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex2) == 1 then
        total = total + be:SYSctlPlayer("HP", "GETHP", playerIndex2, 0)
    end
end
if total == 0 then
    return
end
be:sd("MODELCTRL", nil, -1, "OFCTRL")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossafter")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("MODELCTRL", "e_anomalo", 0, "MOVETRANS", "V<-60,10,-960>/V<0,0,0>")
be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-60,10,-890>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-70,10,-890>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-30,10,-900>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-90,10,-900>/V<0,180,0>")
be:DMsetSD("PLAYER", nil, 0, "SQ_DEMOWALK", 200)
be:DMsetSD("SOUND", nil, -1, "PLAY", "BT_WIN03", 270)
be:DMsetSD("PLAYER", nil, 0, "SQ_DEMOWAIT", 305)
be:DMsetSD("MODELCTRL", "g_000boost1", -1, "SQ_DDMG", 305)
be:DMsetSD("PLAYER", nil, -1, "SQ_ENJOY", 310)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMchkSD("PLAYER", be:SYSgetPlayerName(0), 0, "ISSEQNAME", "SQ_ENJOY", "!=0")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN")
be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "TALKFONT01/font00/CENTER")
g_talk = "mess"
g_page = 0
g_messPlayerNo = 0
local total2 = 0
local total3 = 0
for playerIndex2 = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex2) == 1 then
        total2 = total2 + be:SYSctlPlayer("HP", "GETHP", playerIndex2, 0)
        total3 = total3 + be:SYSctlPlayer("HP", "GETMHP", playerIndex2, 0)
    end
end
local local_4 = total2 * 100 / total3
if be:SYSctlPlayer("HP", "GETHP", playerIndex, 0) == 1 then
    be:FLGset(566, 1)
elseif local_4 < 80 then
    be:FLGset(563, 1)
elseif local_4 < 100 then
    be:FLGset(564, 1)
else
    be:FLGset(565, 1)
end
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "==0")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
funcOneMessage(mswk61069)
if be:FLGisOn(566) == 1 then
    funcOneMessage(mswk61087)
elseif be:FLGisOn(565) == 1 then
    funcOneMessage(mswk61089)
elseif be:FLGisOn(564) == 1 then
    funcOneMessage(mswk61088)
else
    funcOneMessage(mswk61070)
end
be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossdoor")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("MODELCTRL", "g_d2door", 8, "SQ_SWON", 20)
be:DMsetSD("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 35)
be:DMsetSD("MODELCTRL", "g_d2door", 9, "SQ_SWON", 20)
be:DMsetSD("HITLANDMODEL", "doorwall10", 0, "OFFHIT", 35)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_THEME", 60)
be:DMrun()
be:FLGset(130, 1)
be:FLGset(387, 1)
