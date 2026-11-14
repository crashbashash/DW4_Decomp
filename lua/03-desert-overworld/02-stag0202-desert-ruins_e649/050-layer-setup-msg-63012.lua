mswk63012 = "DMINFOFONT01/font00/I<9>"
mswk63013 = "DMINFOFONT02/font00/I<10>"
mswk63014 = "DMINFOFONT02/font01/I<11>"
mswk63015 = "DMINFOFONT02/font02/I<12>"
if be:FLGisOn(359) == 0 then
    if be:FLGisOn(63) == 0 then
        g_delayTime = 410
        be:FLGset(359, 1)
        be:sd("MODELCTRL", nil, -1, "OFCTRL")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Sdc0202a")
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-00", 10)
        be:DMchkSD("MODELCTRL", "e_arachne", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
        funcOpenDigimonInfoWin(mswk63012, mswk63013, mswk63014, mswk63015, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 30)
        be:DMsetSD("ENEMY", "e_arachne", -1, "SQ_ERAS", 30)
        be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT", 30)
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 40)
        be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 70)
        be:DMsetSD("MATCTRL", nil, -1, "RESTART", 70)
        be:DMrun()
    elseif be:FLGisOn(63) == 1 then
        if be:PLAYERgetPos() == 0 then
            funcStageIn("stay")
        elseif be:PLAYERgetPos() == 1 then
            funcStageIn("stay")
        elseif be:PLAYERgetPos() == 2 then
            funcStageIn("trans")
        elseif be:PLAYERgetPos() == 3 then
            funcStageIn("stay")
        end
    end
elseif be:FLGisOn(359) == 1 then
    if be:PLAYERgetPos() == 0 then
        funcStageIn("stay")
    elseif be:PLAYERgetPos() == 1 then
        funcStageIn("stay")
    elseif be:PLAYERgetPos() == 2 then
        funcStageIn("trans")
    elseif be:PLAYERgetPos() == 3 then
        funcStageIn("stay")
    end
end
if be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 27, 0, 0) == 1 then
    local random = be:SYSgetRandom(300)
    if random >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif random >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif random >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif random >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif random >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif random >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 28, 0, 0) == 1 then
    local random = be:SYSgetRandom(240)
    if random >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif random >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif random >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif random >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif random >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif random >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 29, 0, 0) == 1 then
    local random = be:SYSgetRandom(180)
    if random >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif random >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif random >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif random >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif random >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif random >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 29, 0, 0) == 0 and be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 28, 0, 0) == 0 and be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 27, 0, 0) == 0 then
    local random = be:SYSgetRandom(420)
    if random >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif random >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif random >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif random >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif random >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif random >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
end
if be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 27, 0, 0) == 1 then
    local random = be:SYSgetRandom(300)
    if random >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b00")
    elseif random >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b01")
    elseif random >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b02")
    elseif random >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b03")
    elseif random >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b04")
    elseif random >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 28, 0, 0) == 1 then
    local random = be:SYSgetRandom(240)
    if random >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b00")
    elseif random >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b01")
    elseif random >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b02")
    elseif random >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b03")
    elseif random >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b04")
    elseif random >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 29, 0, 0) == 1 then
    local random = be:SYSgetRandom(180)
    if random >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b00")
    elseif random >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b01")
    elseif random >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b02")
    elseif random >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b03")
    elseif random >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b04")
    elseif random >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 29, 0, 0) == 0 and be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 28, 0, 0) == 0 and be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 27, 0, 0) == 0 then
    local random = be:SYSgetRandom(420)
    if random >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b00")
    elseif random >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b01")
    elseif random >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b02")
    elseif random >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b03")
    elseif random >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b04")
    elseif random >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b05")
    end
end
funcPlayerStatusSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
