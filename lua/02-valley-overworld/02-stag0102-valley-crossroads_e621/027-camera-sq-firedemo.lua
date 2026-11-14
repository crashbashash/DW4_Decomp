if be:MATisPlayer() == 1 then
    if be:MDLisLive("g_barrelshotz01", 0) ~= 0 and be:MDLisLive("g_barrelshotz01", 1) ~= 0 then
        if g_tempFLG03 ~= 1 then
            be:sd("MODELCTRL", nil, -1, "OFCTRL")
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
            be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Slope", 0)
            be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
            be:DMsetSD("MODELCTRL", "g_barrelshotz01", -1, "ONCTRL", 2)
            be:DMsetSD("MODELCTRL", "g_barrelshotz01", 0, "SQ_FIREDEMO", 2)
            be:DMsetSD("MODELCTRL", "g_barrelshotz01", 1, "SQ_FIREDEMO", 12)
            be:DMsetSD("MODELCTRL", "g_barrelshotz01", 0, "SQ_FIREDEMO", 54)
            be:DMsetSD("MODELCTRL", "g_barrelshotz01", 1, "SQ_FIREDEMO", 74)
            be:DMsetSD("MODELCTRL", "g_barrelshotz01", 0, "SQ_FIREDEMO", 106)
            be:DMsetSD("MODELCTRL", "g_barrelshotz01", 1, "SQ_FIREDEMO", 126)
            be:DMsetSD("MODELCTRL", "g_barrelshotz01", 0, "SQ_FIREDEMO", 158)
            be:DMsetSD("MODELCTRL", "g_barrelshotz01", 1, "SQ_FIREDEMO", 179)
            be:DMsetSD("MODELCTRL", "g_barrelshotz01", 0, "SQ_FIREDEMO", 210)
            be:DMsetSD("MODELCTRL", "g_barrelshotz01", 1, "SQ_FIREDEMO", 231)
            be:DMsetSD("MODELCTRL", "g_barrelshotz01", 0, "SQ_FIREDEMO", 262)
            be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET")
            be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 0)
            be:DMsetSD("MODELCTRL", "g_barrelshotz01", -1, "SQ_POWERON", 0)
            be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 0)
            be:DMrun()
            g_tempFLG03 = 1
        else
            be:sd("MODELCTRL", "g_barrelshotz01", -1, "SQ_POWERON")
        end
    else
        be:sd("MODELCTRL", "g_barrelshotz01", -1, "SQ_POWERON")
    end
else
    be:sd("MODELCTRL", "g_barrelshotz01", -1, "SQ_POWEROF")
end
