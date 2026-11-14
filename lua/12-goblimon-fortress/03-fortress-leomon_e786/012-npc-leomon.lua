if be:MATisPlayer() == 1 and be:FLGisOn(20) == 0 and be:DMgetCount() <= 0 then
    g_messPlayerNo = 0
    if be:DMgetCount() == -1 then
        be:sd("SUBWND", nil, -1, "REMOVE")
        be:DMchkSD("SUBWND", nil, -1, "ISRUN", "!=0")
    end
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "ST_GOBLI/F<1.0>/F<0.0>/F<120>")
    be:DMsetSD("SOUND", nil, -1, "BGMSTOP", 121)
    be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "AM_GOBLI/F<1.0>/F<0.0>/F<30>")
    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LEOMN", 31)
    be:sd("PLAYER", nil, -1, "SQ_WAIT")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "leomon", 60)
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
    be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<5,10,145>/V<0,0,0>")
    be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<5,10,125>/V<0,0,0>")
    be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-5,10,135>/V<0,0,0>")
    be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<15,10,135>/V<0,0,0>")
    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
    be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "DM_LEOMN", 5)
    be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "AM_GOBLI", 5)
    be:DMsetSD("MODELCTRL", "g_energyfieldz05", 1, "SQ_SWON", 90)
    be:sd("HITLANDMODEL", "hitenergyfieldz051", 0, "OFFHIT")
    be:DMchkSD("MODELCTRL", "g_energyfieldz05", 1, "ISSEQNAME", "SQ_SWON", "==0")
    be:DMchkSD("MODELCTRL", "g_energyfieldz05", 1, "ISSEQNAME", "SQ_SWON", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "leomon2", 60)
    be:DMchkSD("SOUND", nil, -1, "ISALLREADY", "!=1")
    be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "DM_LEOMN", 90)
    be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "AM_GOBLI", 180)
    be:DMsetSD("MODELCTRL", "n_leomon", 0, "SQ_KYRO", 120)
    be:DMsetSD("MODELCTRL", "n_leomon", 0, "SQ_TALK", 240)
    be:DMchkSD("MODELCTRL", "n_leomon", 0, "ISSEQNAME", "SQ_TALK", "==0")
    funcOpenMessage("talk", "n_leomon", "I")
    mswk30101 = "TALKFONT02/font00/I<12>"
    funcOneMessage(mswk30101)
    funcCloseMessage("talk", "n_leomon", "I", 0, "demo")
    be:DMsetSD("MODELCTRL", "n_leomon", 0, "SQ_TALK", 30)
    be:DMchkSD("MODELCTRL", "n_leomon", 0, "ISSEQNAME", "SQ_TALK", "==0")
    funcOpenMessage("talk", "n_leomon", "I")
    mswk30102 = "TALKFONT02/font00/I<13>"
    funcOneMessage(mswk30102)
    funcCloseMessage("talk", "n_leomon", "I", 0, "demo")
    be:DMsetSD("MODELCTRL", "n_leomon", 0, "SQ_TALK", 30)
    be:DMchkSD("MODELCTRL", "n_leomon", 0, "ISSEQNAME", "SQ_TALK", "==0")
    funcOpenMessage("talk", "n_leomon", "I")
    mswk30103 = "TALKFONT02/font00/I<14>"
    funcOneMessage(mswk30103)
    funcCloseMessage("talk", "n_leomon", "I", 0, "demo")
    be:DMsetSD("MODELCTRL", "n_leomon", 0, "SQ_TALK", 30)
    be:DMchkSD("MODELCTRL", "n_leomon", 0, "ISSEQNAME", "SQ_TALK", "==0")
    funcOpenMessage("talk", "n_leomon", "I")
    mswk30104 = "TALKFONT02/font00/I<15>"
    funcOneMessage(mswk30104)
    funcCloseMessage("talk", "n_leomon", "I", 0, "demo")
    be:DMsetSD("MODELCTRL", "n_leomon", 0, "SQ_TALK", 30)
    be:DMchkSD("MODELCTRL", "n_leomon", 0, "ISSEQNAME", "SQ_TALK", "==0")
    funcOpenMessage("talk", "n_leomon", "I")
    mswk30105 = "TALKFONT02/font00/I<16>"
    funcOneMessage(mswk30105)
    mswk30106 = "TALKFONT02/font00/I<17>"
    funcOneMessage(mswk30106)
    mswk30107 = "TALKFONT02/font00/I<18>"
    funcOneMessage(mswk30107)
    funcCloseMessage("talk", "n_leomon", "I", 0, "demo")
    be:DMsetSD("MODELCTRL", "n_leomon", 0, "SQ_TALK", 60)
    be:DMchkSD("MODELCTRL", "n_leomon", 0, "ISSEQNAME", "SQ_TALK", "==0")
    funcOpenMessage("talk", "n_leomon", "I")
    mswk30108 = "TALKFONT02/font00/I<19>"
    funcOneMessage(mswk30108)
    mswk30109 = "TALKFONT02/font00/I<20>"
    funcOneMessage(mswk30109)
    funcCloseMessage("talk", "n_leomon", "I", 0, "demo")
    be:DMsetSD("MODELCTRL", "n_leomon", 0, "SQ_EXIT", 20)
    be:DMchkSD("MODELCTRL", "n_leomon", 0, "ISRUN", "!=0")
    local local_0
    local offset = 40
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_EXIT", offset)
            offset = offset + 20
        end
    end
    be:DMsetSD("NDMWPANEL", nil, -1, "NOGATEDISK", "I<0>")
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", offset + 40)
    be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_STCHANGELP", "==0")
    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<1>", 1)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML02", 1)
    be:FLGset(20, 1)
    be:DMrun()
else
end
