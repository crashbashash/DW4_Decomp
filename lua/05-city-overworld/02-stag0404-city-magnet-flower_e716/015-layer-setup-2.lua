g_bluemagnet00 = -1
g_bluemagnet01 = -1
g_bluemagnet02 = -1
g_bluemagnet03 = -1
g_bluemagnet04 = -1
g_redmagnet00 = 1
g_redmagnet01 = 1
g_redmagnet02 = 1
g_redmagnet03 = 1
g_redmagnet04 = 1
if be:FLGisOn(492) == 1 then
    be:FLGset(492, 0)
end
if be:PLAYERgetPos() == 0 then
    funcStageIn("stay")
end
funcPlayerStatusSet()
be:sd("MODELCTRL", "r_starshipz041", 0, "SQ_WAIT")
funcFailDemo = function()
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 then
            local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
        end
    end
    if local_1 ~= 0 then
        be:sd("HITLANDMODEL", "hitmaincorez04", 0, "ONHIT", 30)
        be:sd("HITLANDMODEL", "hitmaincorez05", 0, "ONHIT", 30)
        if be:FLGisOn(492) == 1 then
            be:FLGset(492, 0)
            g_messPlayerNo = 0
            be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "CTowerFront", 120)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR", 120)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR", 120)
            be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
            be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
            be:DMsetSD("MODELCTRL", "g_maincorez04", 0, "SQ_R270T00", 30)
            be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "CTowerTop", 120)
            be:DMchkSD("MODELCTRL", "g_maincorez04", 0, "ISSEQNAME", "SQ_R270T00", "==0")
            be:DMchkSD("MODELCTRL", "g_maincorez04", 0, "ISSEQNAME", "SQ_R270T00", "!=0")
            be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 60)
            be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 90)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 60)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 60)
        else
            be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        end
    end
end
funcCorrectDemo = function() end
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
