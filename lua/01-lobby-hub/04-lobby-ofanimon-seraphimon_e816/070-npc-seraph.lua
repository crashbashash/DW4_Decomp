if be:MATisPlayer() == 1 and be:FLGisOn(4) == 1 and be:FLGisOn(326) == 0 and be:FLGisOn(335) == 1 and be:DMgetCount() <= 0 then
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
    be:DMsetSD("SOUND", nil, -1, "PLAY", "DM_SERAF", 130)
    be:sd("PLAYER", nil, -1, "SQ_WAIT")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "seratalk2")
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<100,60,-205>/V<0,-180,0>")
    be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<100,60,-185>/V<0,-180,0>")
    be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<110,60,-195>/V<0,-180,0>")
    be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<90,60,-195>/V<0,-180,0>")
    be:DMsetSD("MODELCTRL", "n_seraph", 0, "SQ_TALK", 150)
    be:DMchkSD("MODELCTRL", "n_seraph", 0, "ISSEQNAME", "SQ_TALK", "!=0")
    be:DMchkSD("MODELCTRL", "n_seraph", 0, "ISSEQNAME", "SQ_TALK", "==0")
    funcOpenMessage("talk", "n_seraph", "ZtB")
    mswk30601 = "TALKFONT02/font00/I<362>"
    funcOneMessage(mswk30601)
    mswk30602 = "TALKFONT02/font00/I<363>"
    funcOneMessage(mswk30602)
    funcCloseMessage("talk", "n_seraph", "ZtB", 0, "demo")
    be:DMsetSD("MODELCTRL", "n_seraph", 0, "SQ_TALK", 60)
    be:DMchkSD("MODELCTRL", "n_seraph", 0, "ISSEQNAME", "SQ_TALK", "==0")
    funcOpenMessage("talk", "n_seraph", "ZtB")
    mswk30603 = "TALKFONT02/font00/I<364>"
    funcOneMessage(mswk30603)
    funcCloseMessage("talk", "n_seraph", "ZtB", 0, "demo")
    be:DMsetSD("MODELCTRL", "n_seraph", 0, "SQ_TALK", 60)
    be:DMchkSD("MODELCTRL", "n_seraph", 0, "ISSEQNAME", "SQ_TALK", "==0")
    funcOpenMessage("talk", "n_seraph", "ZtB")
    mswk30604 = "TALKFONT02/font00/I<365>"
    funcOneMessage(mswk30604)
    mswk30605 = "TALKFONT02/font00/I<366>"
    funcOneMessage(mswk30605)
    funcCloseMessage("talk", "n_seraph", "ZtB", 0, "demo")
    be:DMsetSD("MODELCTRL", "n_seraph", 0, "SQ_TALK", 60)
    be:DMchkSD("MODELCTRL", "n_seraph", 0, "ISSEQNAME", "SQ_TALK", "==0")
    funcOpenMessage("talk", "n_seraph", "ZtB")
    mswk30606 = "TALKFONT02/font00/I<367>"
    funcOneMessage(mswk30606)
    mswk30607 = "TALKFONT02/font00/I<368>"
    funcOneMessage(mswk30607)
    mswk30608 = "TALKFONT02/font00/I<369>"
    funcOneMessage(mswk30608)
    funcCloseMessage("talk", "n_seraph", "ZtB", 0, "demo")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 60)
    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 60)
    be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "DM_SERAF/F<1.0>/F<0.0>/F<120>")
    be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "DM_SERAF", 121)
    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_COMMA", 130)
    be:FLGset(326, 1)
    be:FLGset(4, 0)
    be:FLGset(5, 1)
    be:DMrun()
end
