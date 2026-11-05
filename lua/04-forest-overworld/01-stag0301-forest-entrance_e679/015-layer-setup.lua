mswk63028 = "DMINFOFONT01/font00/I<9>"
mswk63029 = "DMINFOFONT02/font00/I<10>"
mswk63030 = "DMINFOFONT02/font01/I<11>"
mswk63031 = "DMINFOFONT02/font02/I<12>"
mswk63032 = "DMINFOFONT01/font00/I<13>"
mswk63033 = "DMINFOFONT02/font00/I<10>"
mswk63034 = "DMINFOFONT02/font01/I<14>"
mswk63035 = "DMINFOFONT02/font02/I<15>"
if be:FLGisOn(360) == 0 then
    g_delayTime = 630
    if local_0 <= 50 then
        be:FLGset(360, 1)
        be:sd("MODELCTRL", nil, -1, "OFCTRL")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Sdc0301a")
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-89", 10)
        be:DMchkSD("MODELCTRL", "e_otama", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
        funcOpenDigimonInfoWin(mswk63028, mswk63029, mswk63030, mswk63031, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 30)
        be:DMsetSD("ENEMY", "e_otama", -1, "SQ_ERAS", 30)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "!=0")
        be:DMchkSD("MODELCTRL", "e_otama", -1, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 40)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLIN30", "==0")
    elseif local_0 <= 100 then
        be:FLGset(360, 1)
        be:sd("MODELCTRL", nil, -1, "OFCTRL")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Sdc0301b")
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-90", 10)
        be:DMchkSD("MODELCTRL", "e_geko", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
        funcOpenDigimonInfoWin(mswk63032, mswk63033, mswk63034, mswk63035, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 30)
        be:DMsetSD("ENEMY", "e_geko", -1, "SQ_ERAS", 30)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "!=0")
        be:DMchkSD("MODELCTRL", "e_geko", -1, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 40)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLIN30", "==0")
    end
elseif be:PLAYERgetPos() == 0 then
    g_delayTime = 220
end
if be:PLAYERgetPos() == 0 then
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "campoint00")
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 then
            be:DMsetSD("PLAYER", be:SYSgetPlayerName(local_2), local_2, "SQ_ENTR", local_1)
            local_1 = local_1 + 20
        end
    end
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
    be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
    be:DMsetSD("MATCTRL", nil, -1, "RESTART")
    be:DMrun()
elseif be:PLAYERgetPos() == 1 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 2 then
    funcStageIn("trans")
elseif be:PLAYERgetPos() == 3 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 4 then
    funcStageIn("trans")
elseif be:PLAYERgetPos() == 5 then
    funcStageIn("stay")
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
