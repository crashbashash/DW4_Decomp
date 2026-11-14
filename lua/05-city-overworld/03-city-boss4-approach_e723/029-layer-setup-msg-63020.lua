mswk63020 = "DMINFOFONT01/font00/I<9>"
mswk63021 = "DMINFOFONT02/font00/I<10>"
mswk63022 = "DMINFOFONT02/font01/I<11>"
mswk63023 = "DMINFOFONT02/font02/I<12>"
if be:FLGisOn(363) == 0 then
    g_delayTime = 410
    be:FLGset(363, 1)
    be:sd("MODELCTRL", nil, -1, "OFCTRL")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Sdc0404a")
    be:DMsetSD("GENERATER", nil, -1, "START", "GENE-01", 60)
    be:DMchkSD("MODELCTRL", "e_impdra", -1, "ISRUN", "==0")
    be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
    funcOpenDigimonInfoWin(mswk63020, mswk63021, mswk63022, mswk63023, 120)
    be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 30)
    be:DMsetSD("ENEMY", "e_impdra", -1, "SQ_ERAS", 30)
    be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT", 30)
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 40)
    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 70)
    be:DMsetSD("MATCTRL", nil, -1, "RESTART", 70)
    be:DMrun()
elseif be:FLGisOn(363) == 1 and be:PLAYERgetPos() == 0 then
    funcStageIn("stay")
end
funcPlayerStatusSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
