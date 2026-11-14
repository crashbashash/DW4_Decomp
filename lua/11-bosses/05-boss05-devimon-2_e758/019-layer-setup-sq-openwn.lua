be:DMsetSD("SOUND", nil, -1, "BGMSTOP")
be:sd("NDMWPANEL", nil, -1, "NOGATEDISK", "I<1>")
be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_BOS01")
be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "d2TRNS01")
be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "d2FADE01")
be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "BT_DEVI2")
be:DMchkSD("SOUND", nil, -1, "ISALLREADY", "!=1")
be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "BT_DEVI2")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "entry")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR", 10)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60")
be:DMsetSD("GENERATER", nil, -1, "START", "GENE-00", 0)
be:DMsetSD("MODELCTRL", "f_devl23", 0, "GENERATE", "V<0.0,10.0,0.0>/V<0.0,0.0,0.0>/SQ_ENTR", 0)
be:DMsetSD("ENEMY", nil, -1, "OFCTRL", 1)
be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "d2TRNS01")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET")
be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT", 2)
be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "ENABLE", 2)
be:DMsetSD("ENEMY", nil, -1, "ONCTRL", 3)
be:DMrun()
if not g_delayTime then
    g_delayTime = 340
end
local local_0
be:sd("MODELCTRL", "i_stpnl00", 0, "SQ_OPEN", g_delayTime)
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        if playerIndex == 0 then
            be:sd("MODELCTRL", "i_stpnl01", 0, "SQ_OPEN", g_delayTime)
            be:sd("MODELCTRL", "i_stpnl02", 0, be:SYSgetPlayerName(playerIndex), g_delayTime)
            be:sd("MODELCTRL", "i_stpnl03", 0, "SQ_OPENWN", g_delayTime)
            be:sd("MODELCTRL", "i_stpnl04", 0, "SQ_OPENWN", g_delayTime)
            be:sd("MODELCTRL", "i_stpnl05", 0, "SQ_WAIT", g_delayTime)
        elseif playerIndex == 1 then
            be:sd("MODELCTRL", "i_stpnl01", 1, "SQ_OPEN", g_delayTime + 5)
            be:sd("MODELCTRL", "i_stpnl02", 1, be:SYSgetPlayerName(playerIndex), g_delayTime + 5)
            be:sd("MODELCTRL", "i_stpnl03", 1, "SQ_OPENWN", g_delayTime + 5)
            be:sd("MODELCTRL", "i_stpnl04", 1, "SQ_OPENWN", g_delayTime + 5)
            be:sd("MODELCTRL", "i_stpnl05", 1, "SQ_WAIT", g_delayTime + 5)
        elseif playerIndex == 2 then
            be:sd("MODELCTRL", "i_stpnl01", 2, "SQ_OPEN", g_delayTime + 10)
            be:sd("MODELCTRL", "i_stpnl02", 2, be:SYSgetPlayerName(playerIndex), g_delayTime + 10)
            be:sd("MODELCTRL", "i_stpnl03", 2, "SQ_OPENWN", g_delayTime + 10)
            be:sd("MODELCTRL", "i_stpnl04", 2, "SQ_OPENWN", g_delayTime + 10)
            be:sd("MODELCTRL", "i_stpnl05", 2, "SQ_WAIT", g_delayTime + 10)
        elseif playerIndex == 3 then
            be:sd("MODELCTRL", "i_stpnl01", 3, "SQ_OPEN", g_delayTime + 15)
            be:sd("MODELCTRL", "i_stpnl02", 3, be:SYSgetPlayerName(playerIndex), g_delayTime + 15)
            be:sd("MODELCTRL", "i_stpnl03", 3, "SQ_OPENWN", g_delayTime + 15)
            be:sd("MODELCTRL", "i_stpnl04", 3, "SQ_OPENWN", g_delayTime + 15)
            be:sd("MODELCTRL", "i_stpnl05", 3, "SQ_WAIT", g_delayTime + 15)
        end
    end
end
be:sd("MODELCTRL", "i_bosshp05", 0, "GENERATE", "V<0,205,0>/SQ_OPEN", g_delayTime)
be:sd("METERCTRL", "bshp05", 0, "SETMODELHP", "f_devl22/I<0>", g_delayTime + 10)
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
