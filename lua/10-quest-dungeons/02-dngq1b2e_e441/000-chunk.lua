for local_2 = 0, 3 do
    if be:SYSisJoinPlayer(local_2) == 1 then
        local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
    end
end
if local_1 == 0 then
    be:sd("MODELCTRL", "i_timenm0", 0, "SQ_STOP")
elseif be:MDLisCallName("down") == 1 then
    if be:COUNTERget(0) ~= 0 then
        if g_counter_sec == 0 then
            g_counter_sec = 59
        else
            g_counter_sec = g_counter_sec + -1
        end
        if g_counter_sec == 59 then
            g_counter_min = g_counter_min + -1
            if minNum == -1 then
                be:sd("NUMBERCTRL", "timenm0", 0, "SETVALUE", "I<" .. g_counter_min .. ">")
                be:sd("MODELCTRL", "i_timenm0", 0, "SQ_STOP", 10)
            else
                be:sd("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
                be:sd("NUMBERCTRL", "timenm0", 0, "SETVALUE", "I<" .. g_counter_min .. ">")
            end
        end
        be:sd("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
        be:COUNTERset(0, local_2)
    else
    end
end
if be:MDLisCallName("up") == 1 then
    if be:COUNTERget(0) < 3600 + -1 then
        be:COUNTERset(0, local_2)
        g_counter_min = floor(be:COUNTERget(0) / 60)
        g_counter_sec = be:COUNTERget(0) - 60 * g_counter_min
        be:sd("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
        be:sd("NUMBERCTRL", "timenm0", 0, "SETVALUE", "I<" .. g_counter_min .. ">")
    else
        be:sd("MODELCTRL", "i_timenm0", 0, "SQ_STOP")
    end
end
