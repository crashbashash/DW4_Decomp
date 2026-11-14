be:sd("PLAYER", nil, -1, "SQ_FALL")
g_deadCheck = 0
be:sd("PLAYER", nil, -1, "OFCTRL")
be:sd("ENEMY", nil, -1, "OFCTRL")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLIN60", "==0")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLIN60", "!=0")
be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "ENABLE")
g_messPlayerNo = 0
funcOpenMessage("mess")
mswk62007 = "TALKFONT01/font00/I<0>"
funcOneMessage(mswk62007)
mswk62008 = "TALKFONT01/font00/I<1>"
funcOneMessage(mswk62008)
funcCloseMessage("mess")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
g_delayTime = 0
local local_0
be:DMsetSD("MODELCTRL", "i_stpnl00", 0, "SQ_OPEN", g_delayTime)
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        if playerIndex == 0 then
            be:DMsetSD("MODELCTRL", "i_stpnl01", 0, "SQ_OPEN", g_delayTime)
            be:DMsetSD("MODELCTRL", "i_stpnl02", 0, be:SYSgetPlayerName(playerIndex), g_delayTime)
            be:DMsetSD("MODELCTRL", "i_stpnl03", 0, "SQ_OPENWN", g_delayTime)
            be:DMsetSD("MODELCTRL", "i_stpnl04", 0, "SQ_OPENWN", g_delayTime)
            be:DMsetSD("MODELCTRL", "i_stpnl05", 0, "SQ_WAIT", g_delayTime)
        elseif playerIndex == 1 then
            be:DMsetSD("MODELCTRL", "i_stpnl01", 1, "SQ_OPEN", g_delayTime + 5)
            be:DMsetSD("MODELCTRL", "i_stpnl02", 1, be:SYSgetPlayerName(playerIndex), g_delayTime + 5)
            be:DMsetSD("MODELCTRL", "i_stpnl03", 1, "SQ_OPENWN", g_delayTime + 5)
            be:DMsetSD("MODELCTRL", "i_stpnl04", 1, "SQ_OPENWN", g_delayTime + 5)
            be:DMsetSD("MODELCTRL", "i_stpnl05", 1, "SQ_WAIT", g_delayTime + 5)
        elseif playerIndex == 2 then
            be:DMsetSD("MODELCTRL", "i_stpnl01", 2, "SQ_OPEN", g_delayTime + 10)
            be:DMsetSD("MODELCTRL", "i_stpnl02", 2, be:SYSgetPlayerName(playerIndex), g_delayTime + 10)
            be:DMsetSD("MODELCTRL", "i_stpnl03", 2, "SQ_OPENWN", g_delayTime + 10)
            be:DMsetSD("MODELCTRL", "i_stpnl04", 2, "SQ_OPENWN", g_delayTime + 10)
            be:DMsetSD("MODELCTRL", "i_stpnl05", 2, "SQ_WAIT", g_delayTime + 10)
        elseif playerIndex == 3 then
            be:DMsetSD("MODELCTRL", "i_stpnl01", 3, "SQ_OPEN", g_delayTime + 15)
            be:DMsetSD("MODELCTRL", "i_stpnl02", 3, be:SYSgetPlayerName(playerIndex), g_delayTime + 15)
            be:DMsetSD("MODELCTRL", "i_stpnl03", 3, "SQ_OPENWN", g_delayTime + 15)
            be:DMsetSD("MODELCTRL", "i_stpnl04", 3, "SQ_OPENWN", g_delayTime + 15)
            be:DMsetSD("MODELCTRL", "i_stpnl05", 3, "SQ_WAIT", g_delayTime + 15)
        end
    else
        g_deadCheck = g_deadCheck + 1
    end
end
be:DMsetSD("MODELCTRL", "r_trainz02", 0, "SQ_RAIL00", 20)
be:DMsetSD("MODELCTRL", "g_soukouz02", 0, "SQ_START", 20)
be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_DEATH")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 120)
be:DMrun()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
