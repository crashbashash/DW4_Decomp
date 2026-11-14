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
        else
            be:sd("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
        end
        local local_2 = be:COUNTERget(0) + -1
        be:COUNTERset(0, local_2)
    end
elseif be:MDLisCallName("up") == 1 then
    if be:COUNTERget(0) < 3600 + -1 then
        local local_2 = be:COUNTERget(0) + 1
        be:COUNTERset(0, local_2)
        g_counter_min = floor(be:COUNTERget(0) / 60)
        g_counter_sec = be:COUNTERget(0) - 60 * g_counter_min
        be:sd("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
        be:sd("NUMBERCTRL", "timenm0", 0, "SETVALUE", "I<" .. g_counter_min .. ">")
    else
        be:sd("MODELCTRL", "i_timenm0", 0, "SQ_STOP")
    end
end
