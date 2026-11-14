mswk63016 = "DMINFOFONT01/font00/I<9>"
mswk63017 = "DMINFOFONT02/font00/I<10>"
mswk63018 = "DMINFOFONT02/font01/I<11>"
mswk63019 = "DMINFOFONT02/font02/I<12>"
mswk63112 = "DMINFOFONT01/font00/I<13>"
mswk63113 = "DMINFOFONT02/font00/I<14>"
mswk63114 = "DMINFOFONT02/font01/I<15>"
mswk63115 = "DMINFOFONT02/font02/I<16>"
if be:FLGisOn(376) == 0 and be:FLGisOn(377) == 0 and be:FLGisOn(378) == 0 and be:FLGisOn(379) == 0 and be:FLGisOn(380) == 0 and be:FLGisOn(381) == 0 then
    if be:FLGisOn(362) == 0 then
        g_delayTime = 630
        local random = be:SYSgetRandom(100)
        if random <= 50 then
            be:FLGset(362, 1)
            be:sd("MODELCTRL", nil, -1, "OFCTRL")
            be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Sdc0401a")
            be:DMsetSD("GENERATER", nil, -1, "START", "GENE-54", 10)
            be:DMchkSD("MODELCTRL", "e_infermo", -1, "ISRUN", "==0")
            be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
            funcOpenDigimonInfoWin(mswk63016, mswk63017, mswk63018, mswk63019, 90)
            be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
            be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
            be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
            be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 30)
            be:DMsetSD("ENEMY", "e_infermo", -1, "SQ_ERAS", 30)
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "==0")
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "!=0")
            be:DMchkSD("MODELCTRL", "e_infermo", -1, "ISRUN", "!=0")
            be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 40)
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLIN30", "==0")
        elseif random <= 100 then
            be:FLGset(362, 1)
            be:sd("MODELCTRL", nil, -1, "OFCTRL")
            be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Sdc0401b")
            be:DMsetSD("GENERATER", nil, -1, "START", "GENE-55", 10)
            be:DMchkSD("MODELCTRL", "e_megadra", -1, "ISRUN", "==0")
            be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
            funcOpenDigimonInfoWin(mswk63112, mswk63113, mswk63114, mswk63115, 90)
            be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
            be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
            be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
            be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 30)
            be:DMsetSD("ENEMY", "e_megadra", -1, "SQ_ERAS", 30)
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "==0")
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "!=0")
            be:DMchkSD("MODELCTRL", "e_megadra", -1, "ISRUN", "!=0")
            be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 40)
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLIN30", "==0")
        end
    elseif be:PLAYERgetPos() == 0 then
        g_delayTime = 220
    end
    if be:PLAYERgetPos() == 0 then
        local local_0
        local offset = 100
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "campoint00")
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_ENTR", offset)
                offset = offset + 20
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
        funcStageIn("stay")
    elseif be:PLAYERgetPos() == 3 then
        funcStageIn("trans")
    elseif be:PLAYERgetPos() == 4 then
        funcStageIn("stay")
    elseif be:PLAYERgetPos() == 5 then
        funcStageIn("stay")
    elseif be:PLAYERgetPos() == 6 then
        funcStageIn("stay")
    elseif be:PLAYERgetPos() == 7 then
        funcStageIn("stay")
    elseif be:PLAYERgetPos() == 8 then
        funcStageIn("stay")
    elseif be:PLAYERgetPos() == 9 then
        funcStageIn("stay")
    elseif be:PLAYERgetPos() == 10 then
        funcStageIn("stay")
    elseif be:PLAYERgetPos() == 11 then
        funcStageIn("stay")
    end
elseif be:PLAYERgetPos() == 0 then
    g_delayTime = 220
    local local_0
    local offset = 100
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "campoint00")
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_ENTR", offset)
            offset = offset + 20
        end
    end
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
    be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
    be:DMsetSD("MATCTRL", nil, -1, "RESTART")
    be:DMrun()
elseif be:PLAYERgetPos() == 1 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 2 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 3 then
    funcStageIn("trans")
elseif be:PLAYERgetPos() == 4 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 5 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 6 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 7 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 8 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 9 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 10 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 11 then
    funcStageIn("stay")
end
if be:FLGisOn(6) == 0 and be:FLGisOn(86) == 0 then
    be:sd("GENERATER", nil, -1, "START", "GENE-26b")
    be:sd("GENERATER", nil, -1, "START", "GENE-34b")
    be:sd("GENERATER", nil, -1, "START", "GENE-39b")
    be:sd("GENERATER", nil, -1, "START", "GENE-46b")
    be:sd("GENERATER", nil, -1, "START", "GENE-59b")
    be:sd("GENERATER", nil, -1, "START", "GENE-65b")
    be:sd("GENERATER", nil, -1, "START", "GENE-71b")
    be:sd("GENERATER", nil, -1, "START", "GENE-79b")
else
    if be:FLGisOn(6) ~= 1 then
        if be:FLGisOn(86) == 1 then
        end
    end
    be:sd("GENERATER", nil, -1, "START", "GENE-26")
    be:sd("GENERATER", nil, -1, "START", "GENE-34")
    be:sd("GENERATER", nil, -1, "START", "GENE-39")
    be:sd("GENERATER", nil, -1, "START", "GENE-46")
    be:sd("GENERATER", nil, -1, "START", "GENE-59")
    be:sd("GENERATER", nil, -1, "START", "GENE-65")
    be:sd("GENERATER", nil, -1, "START", "GENE-71")
    be:sd("GENERATER", nil, -1, "START", "GENE-79")
end
funcPlayerStatusSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
