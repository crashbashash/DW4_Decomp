be:sd("SOUND", nil, -1, "PLAY", "AM_DUNGE")
be:sd("SOUND", nil, -1, "PLAY", "DG_CAVE1")
if be:PLAYERgetPos() == 1 then
    funcStageIn("trans")
elseif be:FLGisOn(300) == 1 then
    be:sd("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
    be:sd("PLAYER", nil, -1, "SQ_WAIT", 60)
else
    g_delayTime = 430
    be:FLGset(300, 1)
    be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
    be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT", 60)
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Ddc101b2a", 75)
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMsetSD("GENERATER", nil, -1, "START", "GENE-01", 30)
    be:DMchkSD("MODELCTRL", "e_scum", -1, "ISRUN", "==0")
    be:DMsetSD("ENEMY", "e_scum", -1, "OFCTRL")
    mswk63048 = "DMINFOFONT01/font00/I<9>"
    mswk63049 = "DMINFOFONT02/font00/I<10>"
    mswk63050 = "DMINFOFONT02/font01/I<11>"
    mswk63051 = "DMINFOFONT02/font02/I<12>"
    funcOpenDigimonInfoWin(mswk63048, mswk63049, mswk63050, mswk63051, 30)
    be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 225)
    be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
    be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT")
    be:DMsetSD("ENEMY", "e_scum", -1, "ONCTRL")
    be:DMrun()
end
funcPlayerStatusSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
