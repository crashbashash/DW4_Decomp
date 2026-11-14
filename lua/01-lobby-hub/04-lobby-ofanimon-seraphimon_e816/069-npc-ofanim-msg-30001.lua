if be:MATisPlayer() == 1 then
    if be:FLGisOn(1) == 1 and be:FLGisOn(320) == 0 and be:DMgetCount() <= 0 then
        g_messPlayerNo = 0
        if be:DMgetCount() == -1 then
            be:sd("SUBWND", nil, -1, "REMOVE")
            be:DMchkSD("SUBWND", nil, -1, "ISRUN", "!=0")
        end
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
        be:sd("ENEMY", nil, -1, "OFCTRL")
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "ST_COMMA/F<1.0>/F<0.0>/F<120>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "ST_COMMA", 121)
        be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "DM_OFNI", 125)
        be:sd("PLAYER", nil, -1, "SQ_WAIT")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 30)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<205,60,-100>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<185,60,-100>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<195,60,-90>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<195,60,-110>/V<0,90,0>")
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ofTURN", 60)
        be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TURN", 60)
        be:DMchkSD("MODELCTRL", "n_ofanim", 0, "ISSEQNAME", "SQ_TURN", "!=0")
        be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK", 150)
        be:DMchkSD("MODELCTRL", "n_ofanim", 0, "ISSEQNAME", "SQ_TALK", "!=0")
        be:DMchkSD("MODELCTRL", "n_ofanim", 0, "ISSEQNAME", "SQ_TALK", "==0")
        funcOpenMessage("talk", "n_ofanim", "It@j")
        be:DMchkSD("SOUND", nil, -1, "ISALLREADY", "!=1")
        be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "DM_OFNI", 30)
        mswk30001 = "TALKFONT02/font00/I<322>"
        funcOneMessage(mswk30001)
        funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 60)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK")
        funcOpenMessage("talk", "n_ofanim", "It@j")
        mswk30002 = "TALKFONT02/font00/I<323>"
        funcOneMessage(mswk30002)
        mswk30003 = "TALKFONT02/font00/I<324>"
        funcOneMessage(mswk30003)
        mswk30004 = "TALKFONT02/font00/I<325>"
        funcOneMessage(mswk30004)
        funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 30)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK")
        funcOpenMessage("talk", "n_ofanim", "It@j")
        mswk30005 = "TALKFONT02/font00/I<326>"
        funcOneMessage(mswk30005)
        mswk30006 = "TALKFONT02/font00/I<327>"
        funcOneMessage(mswk30006)
        mswk30007 = "TALKFONT02/font00/I<328>"
        funcOneMessage(mswk30007)
        mswk30008 = "TALKFONT02/font00/I<329>"
        funcOneMessage(mswk30008)
        mswk30009 = "TALKFONT02/font00/I<330>"
        funcOneMessage(mswk30009)
        mswk30010 = "TALKFONT02/font00/I<331>"
        funcOneMessage(mswk30010)
        mswk30011 = "TALKFONT02/font00/I<332>"
        funcOneMessage(mswk30011)
        mswk30012 = "TALKFONT02/font00/I<333>"
        funcOneMessage(mswk30012)
        funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 30)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK")
        funcOpenMessage("talk", "n_ofanim", "It@j")
        mswk30013 = "TALKFONT02/font00/I<334>"
        funcOneMessage(mswk30013)
        mswk30014 = "TALKFONT02/font00/I<335>"
        funcOneMessage(mswk30014)
        mswk30015 = "TALKFONT02/font00/I<336>"
        funcOneMessage(mswk30015)
        mswk30016 = "TALKFONT02/font00/I<337>"
        funcOneMessage(mswk30016)
        funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 60)
        be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 90)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 90)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 90)
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DM_OFNI/F<1.0>/F<0.0>/F<120>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "DM_OFNI", 121)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_COMMA", 130)
        be:FLGset(320, 1)
        be:FLGset(1, 0)
        be:FLGset(2, 1)
        be:DMrun()
    end
    if be:FLGisOn(2) == 1 and be:FLGisOn(67) == 1 and be:FLGisOn(323) == 0 and be:DMgetCount() == 0 then
        g_messPlayerNo = 0
        be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
        be:sd("ENEMY", nil, -1, "OFCTRL")
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 30)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<205,60,-100>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<185,60,-100>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<195,60,-90>/V<0,90,0>")
        be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<195,60,-110>/V<0,90,0>")
        be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK", 120)
        be:DMchkSD("MODELCTRL", "n_ofanim", 0, "ISSEQNAME", "SQ_TALK", "!=0")
        be:DMchkSD("MODELCTRL", "n_ofanim", 0, "ISSEQNAME", "SQ_TALK", "==0")
        funcOpenMessage("talk", "n_ofanim", "It@j")
        mswk30301 = "TALKFONT02/font00/I<338>"
        funcOneMessage(mswk30301)
        mswk30302 = "TALKFONT02/font00/I<339>"
        funcOneMessage(mswk30302)
        funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "ST_COMMA", 50)
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "AM_LOBBY", 50)
        be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "AM_OFNI1", 51)
        be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "QS_HURRY", 59)
        be:DMchkSD("SOUND", nil, -1, "ISALLREADY", "!=1")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "indicator", 60)
        be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "AM_OFNI1", 60)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
        be:DMsetSD("MODELCTRL", "g_indicatorz05", 0, "SQ_SWON", 30)
        be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "QS_HURRY", 180)
        be:DMchkSD("MODELCTRL", "g_indicatorz05", 0, "ISSEQNAME", "SQ_SWON", "==0")
        be:DMchkSD("MODELCTRL", "g_indicatorz05", 0, "ISSEQNAME", "SQ_SWON", "!=0")
        funcOpenMessage("mess")
        mswk30303 = "TALKFONT01/font00/I<340>"
        funcOneMessage(mswk30303)
        funcCloseMessage("mess", "demo")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 40)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK")
        funcOpenMessage("talk", "n_ofanim", "It@j")
        mswk30304 = "TALKFONT02/font00/I<341>"
        funcOneMessage(mswk30304)
        mswk30305 = "TALKFONT02/font00/I<342>"
        funcOneMessage(mswk30305)
        funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 30)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK")
        funcOpenMessage("talk", "n_ofanim", "It@j")
        mswk30306 = "TALKFONT02/font00/I<343>"
        funcOneMessage(mswk30306)
        mswk30307 = "TALKFONT02/font00/I<344>"
        funcOneMessage(mswk30307)
        mswk30308 = "TALKFONT02/font00/I<345>"
        funcOneMessage(mswk30308)
        mswk30309 = "TALKFONT02/font00/I<346>"
        funcOneMessage(mswk30309)
        mswk30310 = "TALKFONT02/font00/I<347>"
        funcOneMessage(mswk30310)
        funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 30)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("MODELCTRL", "n_ofanim", 0, "SQ_TALK")
        funcOpenMessage("talk", "n_ofanim", "It@j")
        mswk30311 = "TALKFONT02/font00/I<348>"
        funcOneMessage(mswk30311)
        mswk30312 = "TALKFONT02/font00/I<349>"
        funcOneMessage(mswk30312)
        mswk30313 = "TALKFONT02/font00/I<350>"
        funcOneMessage(mswk30313)
        funcCloseMessage("talk", "n_ofanim", "It@j", 0, "demo")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "ofani1", 30)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        funcOpenMessage("mess")
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ITEM_GET", 30)
        mswk30314 = "TALKFONT01/font00/I<351>"
        funcOneMessage(mswk30314)
        funcCloseMessage("mess", "demo")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 60)
        be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 90)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 90)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 90)
        be:FLGset(323, 1)
        be:FLGset(2, 0)
        be:FLGset(3, 1)
        be:SYSctlFlagFolder("SET", 3)
        be:DMrun()
    end
    if be:FLGisOn(5) == 1 and be:FLGisOn(327) == 0 and be:FLGisOn(69) == 1 and be:DMgetCount() == 0 then
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
    end
else
end
