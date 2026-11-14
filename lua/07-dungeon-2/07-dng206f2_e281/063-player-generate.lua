if be:MATisPlayer() == 1 then
    local generatePlayer = function(playerIndex, arg_1, delay)
    local local_3 = (be:SYSctlPlayer("MP", "GETMMP", playerIndex, 0) - be:SYSctlPlayer("MP", "GETMP", playerIndex, 0)) * -1
    be:sd("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "GENERATE", arg_1, delay)
    be:sd("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_HIDE", delay)
    be:sd("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_ENTR", delay + 1)
    be:sd("GAMERAM", nil, 0, "ADDHP", "I<" .. playerIndex .. ">/I<0>/I<0>/I<1>", delay + 2)
    be:sd("GAMERAM", nil, 0, "ADDMP", "I<" .. playerIndex .. ">/I<" .. local_3 .. ">", delay + 2)
end
    local local_1
    local ramNo
    local local_3
    local_1 = 0
    ramNo = 3
    for playerIndex = 0, 3 do
        if be:MATisRidePlayer(playerIndex) == 1 then
            local_1 = 1
            if ramNo > playerIndex then
                ramNo = playerIndex
            end
        end
    end
    if local_1 == 1 then
        local posStr
        posStr = be:PLAYERgetPosStr(ramNo, 0, 0, 0)
        if g_fall0 == 1 then
            generatePlayer(0, posStr, 0)
            g_fall0 = 0
        end
        if g_fall1 == 1 then
            generatePlayer(1, posStr, 0)
            g_fall1 = 0
        end
        if g_fall2 == 1 then
            generatePlayer(2, posStr, 0)
            g_fall2 = 0
        end
        if g_fall3 == 1 then
            generatePlayer(3, posStr, 0)
            g_fall3 = 0
        end
        g_fallPos = 24
    end
end
