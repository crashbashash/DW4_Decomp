mswkNPC034 = "TALKFONT03/font00/I<9>"
mswk63076 = "DMINFOFONT01/font00/I<10>"
mswk63077 = "DMINFOFONT02/font00/I<11>"
mswk63078 = "DMINFOFONT02/font01/I<12>"
mswk63079 = "DMINFOFONT02/font02/I<13>"
if be:FLGisOn(361) == 0 then
    if be:FLGisOn(64) == 0 then
        g_delayTime = 410
        be:FLGset(361, 1)
        be:sd("MODELCTRL", nil, -1, "OFCTRL")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Sdc0302a")
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-165", 10)
        be:DMchkSD("MODELCTRL", "e_torta", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
        funcOpenDigimonInfoWin(mswk63076, mswk63077, mswk63078, mswk63079, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 30)
        be:DMsetSD("ENEMY", "e_torta", -1, "SQ_ERAS", 30)
        be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT", 30)
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 40)
        be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 70)
        be:DMsetSD("MATCTRL", nil, -1, "RESTART", 70)
        be:DMrun()
    elseif be:FLGisOn(64) == 1 then
        if be:PLAYERgetPos() == 0 then
            funcStageIn("stay")
        elseif be:PLAYERgetPos() == 1 then
            funcStageIn("trans")
        elseif be:PLAYERgetPos() == 2 then
            funcStageIn("trans")
        elseif be:PLAYERgetPos() == 3 then
            funcStageIn("stay")
        elseif be:PLAYERgetPos() == 4 then
            funcStageIn("stay")
        else
        end
    end
end
if be:FLGisOn(361) == 1 then
    if be:PLAYERgetPos() == 0 then
        funcStageIn("stay")
    elseif be:PLAYERgetPos() == 1 then
        funcStageIn("trans")
    elseif be:PLAYERgetPos() == 2 then
        funcStageIn("trans")
    elseif be:PLAYERgetPos() == 3 then
        funcStageIn("stay")
    elseif be:PLAYERgetPos() == 4 then
        funcStageIn("stay")
    end
end
if be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 27, 0, 0) == 1 then
    if local_0 >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif local_0 >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif local_0 >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif local_0 >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif local_0 >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif local_0 >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 28, 0, 0) == 1 then
    if local_0 >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif local_0 >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif local_0 >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif local_0 >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif local_0 >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif local_0 >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 29, 0, 0) == 1 then
    if local_0 >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif local_0 >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif local_0 >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif local_0 >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif local_0 >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif local_0 >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 29, 0, 0) == 0 and be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 28, 0, 0) == 0 and be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 27, 0, 0) == 0 then
    if local_0 >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif local_0 >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif local_0 >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif local_0 >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif local_0 >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif local_0 >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
end
if be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 27, 0, 0) == 1 then
    if local_0 >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b00")
    elseif local_0 >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b01")
    elseif local_0 >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b02")
    elseif local_0 >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b03")
    elseif local_0 >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b04")
    elseif local_0 >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 28, 0, 0) == 1 then
    if local_0 >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b00")
    elseif local_0 >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b01")
    elseif local_0 >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b02")
    elseif local_0 >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b03")
    elseif local_0 >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b04")
    elseif local_0 >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 29, 0, 0) == 1 then
    if local_0 >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b00")
    elseif local_0 >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b01")
    elseif local_0 >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b02")
    elseif local_0 >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b03")
    elseif local_0 >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b04")
    elseif local_0 >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 29, 0, 0) == 0 and be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 28, 0, 0) == 0 and be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 27, 0, 0) == 0 then
    if local_0 >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b00")
    elseif local_0 >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b01")
    elseif local_0 >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b02")
    elseif local_0 >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b03")
    elseif local_0 >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b04")
    elseif local_0 >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-b05")
    end
end
funcPlayerStatusSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
