if be:MATisPlayer() == 1 and be:FLGisOn(5) == 1 and be:FLGisOn(327) == 0 and be:FLGisOn(69) == 1 and be:DMgetCount() == 0 then
    g_messPlayerNo = 0
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("PLAYER", nil, -1, "SQ_WAIT")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 30)
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "ST_COMMA/F<1.0>/F<0.0>/F<120>")
    be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "ST_COMMA", 121)
    be:DMsetSD("SOUND", nil, -1, "PLAY", "DM_OFNI", 130)
    be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<205,60,-100>/V<0,90,0>")
    be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<185,60,-100>/V<0,90,0>")
    be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<195,60,-90>/V<0,90,0>")
    be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<195,60,-110>/V<0,90,0>")
    be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK", 130)
    be:DMchkSD("MODELCTRL", "n_ofanim", 0, "ISSEQNAME", "SQ_TALK", "!=0")
    be:DMchkSD("MODELCTRL", "n_ofanim", 0, "ISSEQNAME", "SQ_TALK", "==0")
    funcOpenMessage("talk", "n_ofanim", "It@j")
    mswk30701 = "TALKFONT02/font00/I<352>"
    funcOneMessage(mswk30701)
    mswk30702 = "TALKFONT02/font00/I<353>"
    funcOneMessage(mswk30702)
    mswk30703 = "TALKFONT02/font00/I<354>"
    funcOneMessage(mswk30703)
    funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 30)
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK")
    funcOpenMessage("talk", "n_ofanim", "It@j")
    mswk30704 = "TALKFONT02/font00/I<355>"
    funcOneMessage(mswk30704)
    mswk30705 = "TALKFONT02/font00/I<356>"
    funcOneMessage(mswk30705)
    mswk30706 = "TALKFONT02/font00/I<357>"
    funcOneMessage(mswk30706)
    mswk30707 = "TALKFONT02/font00/I<358>"
    funcOneMessage(mswk30707)
    funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 30)
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK")
    funcOpenMessage("talk", "n_ofanim", "It@j")
    mswk30708 = "TALKFONT02/font00/I<359>"
    funcOneMessage(mswk30708)
    mswk30709 = "TALKFONT02/font00/I<360>"
    funcOneMessage(mswk30709)
    mswk30710 = "TALKFONT02/font00/I<361>"
    funcOneMessage(mswk30710)
    funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 60)
    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 90)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 90)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 90)
    be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DM_OFNI/F<1.0>/F<0.0>/F<120>")
    be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "DM_OFNI", 121)
    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_COMMA", 130)
    be:FLGset(327, 1)
    be:FLGset(5, 0)
    be:FLGset(6, 1)
    be:DMrun()
else
end
