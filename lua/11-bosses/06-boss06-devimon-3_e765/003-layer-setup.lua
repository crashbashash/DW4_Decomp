be:DMsetSD("SOUND", nil, -1, "BGMSTOP")
be:sd("NDMWPANEL", nil, -1, "NOGATEDISK", "I<1>")
be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_BOS01")
be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "d3TRNS01")
be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "d3FADE01")
be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "BT_DEVI3")
be:DMchkSD("SOUND", nil, -1, "ISALLREADY", "!=1")
be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "d3TRNS01")
be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "BT_DEVI3", 160)
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "entry")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR", 10)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60")
be:DMsetSD("GENERATER", nil, -1, "START", "GENE-00", 160)
be:DMsetSD("ENEMY", nil, -1, "OFCTRL", 1)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET")
be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT", 2)
be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "ENABLE", 2)
be:DMsetSD("ENEMY", nil, -1, "ONCTRL", 3)
be:DMrun()
if not g_delayTime then
    g_delayTime = 430
end
be:sd("MODELCTRL", "i_stpnl00", 0, "SQ_OPEN", g_delayTime)
for local_1 = 0, 3 do
    if be:SYSisJoinPlayer(local_1) == 1 then
        if local_1 == 0 then
            be:sd("MODELCTRL", "i_stpnl01", 0, "SQ_OPEN", g_delayTime)
            be:sd("MODELCTRL", "i_stpnl02", 0, be:SYSgetPlayerName(local_1), g_delayTime)
            be:sd("MODELCTRL", "i_stpnl03", 0, "SQ_OPENWN", g_delayTime)
            be:sd("MODELCTRL", "i_stpnl04", 0, "SQ_OPENWN", g_delayTime)
            be:sd("MODELCTRL", "i_stpnl05", 0, "SQ_WAIT", g_delayTime)
        elseif local_1 == 1 then
            be:sd("MODELCTRL", "i_stpnl01", 1, "SQ_OPEN", g_delayTime + 5)
            be:sd("MODELCTRL", "i_stpnl02", 1, be:SYSgetPlayerName(local_1), g_delayTime + 5)
            be:sd("MODELCTRL", "i_stpnl03", 1, "SQ_OPENWN", g_delayTime + 5)
            be:sd("MODELCTRL", "i_stpnl04", 1, "SQ_OPENWN", g_delayTime + 5)
            be:sd("MODELCTRL", "i_stpnl05", 1, "SQ_WAIT", g_delayTime + 5)
        elseif local_1 == 2 then
            be:sd("MODELCTRL", "i_stpnl01", 2, "SQ_OPEN", g_delayTime + 10)
            be:sd("MODELCTRL", "i_stpnl02", 2, be:SYSgetPlayerName(local_1), g_delayTime + 10)
            be:sd("MODELCTRL", "i_stpnl03", 2, "SQ_OPENWN", g_delayTime + 10)
            be:sd("MODELCTRL", "i_stpnl04", 2, "SQ_OPENWN", g_delayTime + 10)
            be:sd("MODELCTRL", "i_stpnl05", 2, "SQ_WAIT", g_delayTime + 10)
        elseif local_1 == 3 then
            be:sd("MODELCTRL", "i_stpnl01", 3, "SQ_OPEN", g_delayTime + 15)
            be:sd("MODELCTRL", "i_stpnl02", 3, be:SYSgetPlayerName(local_1), g_delayTime + 15)
            be:sd("MODELCTRL", "i_stpnl03", 3, "SQ_OPENWN", g_delayTime + 15)
            be:sd("MODELCTRL", "i_stpnl04", 3, "SQ_OPENWN", g_delayTime + 15)
            be:sd("MODELCTRL", "i_stpnl05", 3, "SQ_WAIT", g_delayTime + 15)
        end
    end
end
be:sd("MODELCTRL", "i_bosshp06", 0, "GENERATE", "V<0,205,0>/SQ_OPEN", g_delayTime)
be:sd("METERCTRL", "bshp06", 0, "SETMODELHP", "f_devl3/I<0>", g_delayTime + 10)
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
g_FBSwitch = 0
