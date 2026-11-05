mswk63096 = "DMINFOFONT01/font00/I<9>"
mswk63097 = "DMINFOFONT02/font00/I<10>"
mswk63098 = "DMINFOFONT02/font01/I<11>"
mswk63099 = "DMINFOFONT02/font02/I<12>"
mswk63060 = "DMINFOFONT01/font00/I<13>"
mswk63061 = "DMINFOFONT02/font00/I<14>"
mswk63062 = "DMINFOFONT02/font01/I<15>"
mswk63063 = "DMINFOFONT02/font02/I<16>"
if be:FLGisOn(358) == 0 then
    g_delayTime = 630
    if local_0 <= 50 then
        be:FLGset(358, 1)
        be:sd("MODELCTRL", nil, -1, "OFCTRL")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Sdc0201a")
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-49", 10)
        be:DMchkSD("MODELCTRL", "e_mummy", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
        funcOpenDigimonInfoWin(mswk63096, mswk63097, mswk63098, mswk63099, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 30)
        be:DMsetSD("ENEMY", "e_mummy", -1, "SQ_ERAS", 30)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "!=0")
        be:DMchkSD("MODELCTRL", "e_mummy", -1, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 40)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLIN30", "==0")
    elseif local_0 <= 100 then
        be:FLGset(358, 1)
        be:sd("MODELCTRL", nil, -1, "OFCTRL")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Sdc0201b")
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-50", 60)
        be:DMchkSD("MODELCTRL", "e_tyrano", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
        funcOpenDigimonInfoWin(mswk63060, mswk63061, mswk63062, mswk63063, 120)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 30)
        be:DMsetSD("ENEMY", "e_tyrano", -1, "SQ_ERAS", 30)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "!=0")
        be:DMchkSD("MODELCTRL", "e_tyrano", -1, "ISRUN", "!=0")
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
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 5 then
    funcStageIn("trans")
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
funcPlayerStatusSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
