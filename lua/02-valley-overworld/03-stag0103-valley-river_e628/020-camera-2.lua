if be:MATisPlayer() == 1 and g_IFLG09 ~= 1 and be:DMgetCount() == 0 then
    g_IFLG09 = 1
    g_IFLG10 = 0
    be:sd("MODELCTRL", nil, -1, "OFCTRL")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "gate", 30)
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 0)
    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 0)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
    be:DMrun()
    be:sd("MODELCTRL", "g_factgatez06", 0, "SQ_SWON", 60)
end
