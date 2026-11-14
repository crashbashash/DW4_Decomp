mswk63024 = "DMINFOFONT01/font00/I<9>"
mswk63025 = "DMINFOFONT02/font00/I<10>"
mswk63026 = "DMINFOFONT02/font01/I<11>"
mswk63027 = "DMINFOFONT02/font02/I<12>"
mswk63040 = "DMINFOFONT01/font00/I<13>"
mswk63041 = "DMINFOFONT02/font00/I<10>"
mswk63042 = "DMINFOFONT02/font01/I<14>"
mswk63043 = "DMINFOFONT02/font02/I<15>"
mswk63084 = "DMINFOFONT01/font00/I<16>"
mswk63085 = "DMINFOFONT02/font00/I<17>"
mswk63086 = "DMINFOFONT02/font01/I<18>"
mswk63087 = "DMINFOFONT02/font02/I<19>"
if be:FLGisOn(355) == 0 then
    g_delayTime = 630
    local random = be:SYSgetRandom(100)
    if random <= 50 then
        be:FLGset(355, 1)
        be:sd("MODELCTRL", nil, -1, "OFCTRL")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Sdc0101a")
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-21", 10)
        be:DMchkSD("MODELCTRL", "e_goburi", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
        funcOpenDigimonInfoWin(mswk63040, mswk63041, mswk63042, mswk63043, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 30)
        be:DMsetSD("ENEMY", "e_goburi", -1, "SQ_ERAS", 30)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "!=0")
        be:DMchkSD("MODELCTRL", "e_goburi", -1, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 40)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLIN30", "==0")
    elseif random <= 100 then
        be:FLGset(355, 1)
        be:sd("MODELCTRL", nil, -1, "OFCTRL")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Sdc0101c")
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-22", 10)
        be:DMchkSD("MODELCTRL", "e_nume", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
        funcOpenDigimonInfoWin(mswk63084, mswk63085, mswk63086, mswk63087, 90)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 30)
        be:DMsetSD("ENEMY", "e_nume", -1, "SQ_ERAS", 30)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "!=0")
        be:DMchkSD("MODELCTRL", "e_nume", -1, "ISRUN", "!=0")
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
end
funcPlayerStatusSet()
if be:FLGisOn(504) == 0 then
    be:sd("MODELCTRL", "i_breakcur", -1, "SQ_OPEN", g_delayTime)
end
if be:FLGisOn(598) == 1 and be:FLGisOn(599) == 1 and be:FLGisOn(600) == 1 and be:FLGisOn(601) == 1 and be:FLGisOn(602) == 1 and be:FLGisOn(603) == 1 and be:FLGisOn(604) == 1 and be:FLGisOn(605) == 1 and be:FLGisOn(606) == 1 and be:FLGisOn(607) == 1 and be:FLGisOn(608) == 1 and be:FLGisOn(609) == 1 and be:FLGisOn(610) == 1 then
    local playerName = be:SYSgetPlayerName(0)
    if playerName == "p_agumon" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e00")
    elseif playerName == "p_vmon" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e01")
    elseif playerName == "p_girumon" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e02")
    elseif playerName == "p_dorumon" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e03")
    elseif playerName == "p_weregaru" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e04")
    elseif playerName == "p_hekabut" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e05")
    elseif playerName == "p_wargrey" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e06")
    elseif playerName == "p_angelr" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e07")
    elseif playerName == "p_beelzeb" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e08")
    elseif playerName == "p_alpha" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e09")
    elseif playerName == "p_bwargrey" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e10")
    elseif playerName == "p_impdrafm" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e11")
    elseif playerName == "p_impdrapm" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e12")
    elseif playerName == "p_metalgaru" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e13")
    elseif playerName == "p_dukecrim" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e14")
    elseif playerName == "p_susanoo" then
        be:sd("GENERATER", nil, -1, "START", "GENE-e15")
    end
else
    be:sd("GENERATER", nil, -1, "START", "GENE-30")
end
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
