be:sd("SOUND", nil, -1, "PLAY", "AM_DUNGE")
be:sd("SOUND", nil, -1, "PLAY", "DG_CAVE2")
if be:PLAYERgetPos() == 1 then
    funcStageIn("trans")
else
    if be:FLGisOn(301) == 1 then
        be:sd("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
        be:sd("PLAYER", nil, -1, "SQ_WAIT", 60)
        for local_1 = 0, 3 do
            if be:SYSisJoinPlayer(local_1) == 1 then
                be:sd("PLAYER", be:SYSgetPlayerName(local_1), local_1, "SETMETAL", 60)
            end
        end
    end
    g_delayTime = 430
    be:FLGset(301, 1)
    be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
    be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT", 60)
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "dng204b2", 75)
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMsetSD("GENERATER", nil, -1, "START", "INTRO-01", 30)
    be:DMchkSD("MODELCTRL", "e_minotaru", -1, "ISRUN", "==0")
    be:DMsetSD("ENEMY", "e_minotaru", -1, "OFCTRL")
    mswk63108 = "DMINFOFONT01/font00/I<9>"
    mswk63109 = "DMINFOFONT02/font00/I<10>"
    mswk63110 = "DMINFOFONT02/font01/I<11>"
    mswk63111 = "DMINFOFONT02/font02/I<12>"
    funcOpenDigimonInfoWin(mswk63108, mswk63109, mswk63110, mswk63111, 30)
    be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 225)
    be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
    be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT")
    for local_1 = 0, 3 do
        if be:SYSisJoinPlayer(local_1) == 1 then
            be:DMsetSD("PLAYER", be:SYSgetPlayerName(local_1), local_1, "SETMETAL")
        end
    end
    be:DMsetSD("ENEMY", "e_minotaru", -1, "ONCTRL")
    be:DMsetSD("ENEMY", "e_minotaru", -1, "SQ_ERAS")
    be:DMrun()
end
funcPlayerStatusSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
