for local_2 = 0, 3 do
    if be:SYSisJoinPlayer(local_2) == 1 then
        local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
    end
end
if local_1 == 0 then
    be:sd("MODELCTRL", "i_timenm0", 0, "SQ_STOP")
elseif be:MDLisCallName("down") == 1 then
    if be:COUNTERget(0) > 0 then
        if g_counter_sec == 0 then
            g_counter_sec = 59
            g_counter_min = g_counter_min + -1
            be:sd("NUMBERCTRL", "timenm0", 0, "SETVALUE", "I<" .. g_counter_min .. ">")
        else
            g_counter_sec = g_counter_sec + -1
        end
        be:sd("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
        be:COUNTERset(0, local_2)
        if floor(local_2 / 32) * 32 == local_2 then
            be:sd("SOUND", nil, -1, "PLAY", "qsGHOST")
        elseif floor(local_2 / 24) * 24 == local_2 then
            be:sd("SOUND", nil, -1, "PLAY", "qsGHOST")
        end
        if floor(local_2 / 10) * 10 == local_2 then
            be:sd("SOUND", nil, -1, "PLAY", "z3COUNT2")
        else
            be:sd("SOUND", nil, -1, "PLAY", "z3COUNT1")
        end
    else
        be:FLGset(409, 0)
        be:FLGset(378, 0)
        be:FLGset(571, 0)
        be:FLGset(424, 0)
        be:SYSctlFlagFolder("CLR", 11)
        be:DMsetSD("MODELCTRL", "i_timenm0", 0, "SQ_BLINK")
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
        be:DMsetSD("SOUND", nil, -1, "PLAY", "z3COUNT3")
        be:DMsetSD("PLAYER", be:SYSgetPlayerName(0), 0, "SQ_DEAD", 60)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR", 60)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR", 60)
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_GAMEOVER", 110)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
        be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "QS_HURRY/F<1.0>/F<0.0>/F<30>")
        be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "QS_HURRY", 31)
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
        funcOneMessage(mswk61061)
        be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
        be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 1)
        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML11", 1)
        be:DMrun()
    end
end
if be:MDLisCallName("up") == 1 and be:COUNTERget(0) <= 3601 then
    if g_counter_sec == 59 then
        g_counter_sec = 0
    else
        g_counter_sec = g_counter_sec + 1
    end
    if g_counter_sec == 0 then
        g_counter_min = g_counter_min + 1
        if g_counter_min == 60 then
            be:sd("MODELCTRL", "i_timenm0", 0, "SQ_STOP", 10)
        else
            be:sd("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
            be:sd("NUMBERCTRL", "timenm0", 0, "SETVALUE", "I<" .. g_counter_min .. ">")
        end
    end
    be:sd("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
    be:COUNTERset(0, local_2)
end
