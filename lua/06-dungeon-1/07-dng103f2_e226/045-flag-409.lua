be:sd("ENEMY", nil, -1, "OFCTRL")
be:sd("PLAYER2", nil, -1, "OFCTRL")
mswk62009 = "TALKFONT01/font00/I<0>"
if g_fall0 + g_fall1 + g_fall2 + g_fall3 >= 1 then
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
    if g_fallPos == 0 then
        local_1 = g_posTbl00
    elseif g_fallPos == 11 then
        local_1 = g_posTbl11
    elseif g_fallPos == 12 then
        local_1 = g_posTbl12
    elseif g_fallPos == 21 then
        local_1 = g_posTbl21
    elseif g_fallPos == 22 then
        local_1 = g_posTbl22
    elseif g_fallPos == 23 then
        local_1 = g_posTbl23
    elseif g_fallPos == 24 then
        local_1 = g_posTbl24
    elseif g_fallPos == 25 then
        local_1 = g_posTbl25
    elseif g_fallPos == 26 then
        local_1 = g_posTbl26
    elseif g_fallPos == 35 then
        local_1 = g_posTbl35
    elseif g_fallPos == 36 then
        local_1 = g_posTbl36
    elseif g_fallPos == 37 then
        local_1 = g_posTbl37
    elseif g_fallPos == 38 then
        local_1 = g_posTbl38
    elseif g_fallPos == 41 then
        local_1 = g_posTbl41
    elseif g_fallPos == 42 then
        local_1 = g_posTbl42
    elseif g_fallPos == 43 then
        local_1 = g_posTbl43
    elseif g_fallPos == 44 then
        local_1 = g_posTbl44
    elseif g_fallPos == 51 then
        local_1 = g_posTbl51
    elseif g_fallPos == 52 then
        local_1 = g_posTbl52
    elseif g_fallPos == 53 then
        local_1 = g_posTbl53
    end
    be:DMsetSD("MATCTRL", nil, -1, "PAUSE", 0)
    if g_fall0 == 1 then
        local_0(0, local_1[1], 30)
        g_fall0 = 0
    end
    if g_fall1 == 1 then
        local_0(1, local_1[2], 30)
        g_fall1 = 0
    end
    if g_fall2 == 1 then
        local_0(2, local_1[3], 30)
        g_fall2 = 0
    end
    if g_fall3 == 1 then
        local_0(3, local_1[4], 30)
        g_fall3 = 0
    end
    be:DMsetSD("MATCTRL", nil, -1, "RESTART", 40)
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 40)
    be:sd("ENEMY", nil, -1, "ONCTRL", 90)
    be:sd("PLAYER2", nil, -1, "ONCTRL", 90)
    be:DMrun()
elseif be:COUNTERget(2) == 906 then
    be:FLGset(409, 0)
    be:FLGset(381, 0)
    be:FLGset(571, 0)
    be:FLGset(424, 0)
    be:COUNTERset(2, 0)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_GAMEOVER")
    be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
    be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "QS_THEME/F<1.0>/F<0.0>/F<30>")
    be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "QS_THEME", 31)
    be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "QS_DONOT", 32)
    be:DMchkSD("SOUND", nil, -1, "ISREADY", "QS_DONOT", "!=1")
    be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_GAMEOVER", "!=0")
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN")
    be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "TALKFONT01/font00/CENTER")
    g_talk = "mess"
    g_page = 0
    g_messPlayerNo = 0
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
    be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "QS_DONOT")
    funcOneMessage(mswk61090)
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 1)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML11", 1)
    be:DMrun()
elseif be:FLGisOn(508) == 1 then
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:FLGset(508, 0)
    be:DMsetSD("MODELCTRL", "i_stpnl00", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_stpnl01", -1, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_stpnl02", -1, "SQ_CLOSEWN")
    be:DMsetSD("MODELCTRL", "i_stpnl03", -1, "SQ_CLOSEWN")
    be:DMsetSD("MODELCTRL", "i_stpnl04", -1, "SQ_CLOSEWN")
    mswk67043 = "TALKFONT05/font00/I<1>"
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN")
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67043)
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 2)
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67044 = "TALKFONT05/font00/I<2>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67044)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 12)
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67045 = "TALKFONT05/font00/I<3>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67045)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 12)
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "!=0")
    mswk67046 = "TALKFONT05/font00/I<4>"
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN", 120)
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67046)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 12)
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67047 = "TALKFONT05/font00/I<5>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67047)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 12)
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_GAMEOVER")
    be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_GAMEOVER", "!=0")
    mswk67048 = "TALKFONT05/font00/I<6>"
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN")
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67048)
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 2)
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67049 = "TALKFONT05/font00/I<7>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67049)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 12)
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    mswk67050 = "TALKFONT05/font00/I<8>"
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67050)
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 12)
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "!=0")
    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 1)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML11", 1)
    be:DMrun()
else
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_GAMEOVER", 180)
    be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_GAMEOVER", "!=0")
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN")
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk62009)
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT01/font00/SET")
    be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE", 2)
    be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
    be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT01/font00/CLR")
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 1)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML11", 1)
    be:DMrun()
end
