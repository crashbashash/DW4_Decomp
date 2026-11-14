local local_0
local total = 0
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        total = total + be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
    end
end
if total == 0 then
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
        local local_2 = be:COUNTERget(0) + -1
        be:COUNTERset(0, local_2)
        if local_2 < 60 then
            if floor(local_2 / 10) * 10 == local_2 then
                be:sd("SOUND", nil, -1, "PLAY", "z3COUNT2")
            else
                be:sd("SOUND", nil, -1, "PLAY", "z3COUNT1")
            end
        end
    else
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:sd("ENEMY", nil, -1, "OFCTRL")
        be:DMsetSD("SOUND", nil, -1, "PLAY", "z3COUNT3")
        be:FLGset(19, 1)
        be:DMsetSD("MODELCTRL", "i_timenm0", 0, "SQ_BLINK")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR", 60)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR", 60)
        be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN", 60)
        be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "TALKFONT01/font00/CENTER", 60)
        g_talk = "mess"
        g_page = 0
        g_messPlayerNo = 0
        be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
        funcOneMessage(mswk61008)
        be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01")
        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 90)
        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML11", 90)
        be:DMrun()
    end
elseif be:MDLisCallName("up") == 1 and be:COUNTERget(0) <= 3601 then
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
    else
        be:sd("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
    end
    local local_2 = be:COUNTERget(0) + 1
    be:COUNTERset(0, local_2)
end
