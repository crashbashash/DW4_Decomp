local local_0
local total = 0
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        total = total + be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
    end
end
if total == 0 then
    return
end
be:sd("MODELCTRL", nil, -1, "OFCTRL")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossafter")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("MODELCTRL", "e_tonogeko", 0, "MOVETRANS", "V<-340,10,540>/V<0,-90,0>")
be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-410,10,550>/V<0,90,0>")
be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-410,10,530>/V<0,90,0>")
be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-400,10,570>/V<0,90,0>")
be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-400,10,510>/V<0,90,0>")
be:DMsetSD("SOUND", nil, -1, "PLAY", "BT_WIN03", 200)
be:DMsetSD("PLAYER", nil, -1, "SQ_ENJOY", 240)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN")
be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "TALKFONT01/font00/CENTER")
g_talk = "mess"
g_page = 0
g_messPlayerNo = 0
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "==0")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
funcOneMessage(mswk61092)
be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "sbossdoor")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("MODELCTRL", "g_d3door", 18, "SQ_SWON", 20)
be:DMsetSD("HITLANDMODEL", "doorwall19", 0, "OFFHIT", 35)
be:DMsetSD("MODELCTRL", "g_d3door", 19, "SQ_SWON", 20)
be:DMsetSD("HITLANDMODEL", "doorwall20", 0, "OFFHIT", 35)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_THEME", 60)
be:DMrun()
be:FLGset(187, 1)
if be:SYSgetDifficulty() == 0 then
    be:FLGset(447, 1)
elseif be:SYSgetDifficulty() == 1 then
    be:FLGset(449, 1)
elseif be:SYSgetDifficulty() == 2 then
    be:FLGset(451, 1)
end
if be:SYSgetDifficulty() == 0 then
    if be:COUNTERget(3) >= 50 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-E29")
    end
    if be:COUNTERget(3) >= 70 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-E30")
    end
    if be:COUNTERget(3) >= 90 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-E31")
    end
    if be:COUNTERget(3) >= 95 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-E32")
    end
elseif be:SYSgetDifficulty() == 1 then
    if be:COUNTERget(3) >= 50 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-H29")
    end
    if be:COUNTERget(3) >= 70 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-H30")
    end
    if be:COUNTERget(3) >= 90 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-H31")
    end
    if be:COUNTERget(3) >= 95 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-H32")
    end
elseif be:SYSgetDifficulty() == 2 then
    if be:COUNTERget(3) >= 50 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-V29")
    end
    if be:COUNTERget(3) >= 100 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-V30")
    end
    if be:COUNTERget(3) >= 120 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-V31")
    end
    if be:COUNTERget(3) >= 125 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-V32")
    end
end
