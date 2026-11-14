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
    for playerIndex = 0, 3 do
        if be:MATisRidePlayer(playerIndex) == 1 then
            be:sd("GAMERAM", nil, 0, "ADDHP", "I<" .. playerIndex .. ">/I<-99999>")
            if playerIndex == 0 then
                g_fall0 = 1
            elseif playerIndex == 1 then
                g_fall1 = 1
            elseif playerIndex == 2 then
                g_fall2 = 1
            else
                g_fall3 = 1
            end
            be:sd("PLAYER", nil, playerIndex, "REMOVE")
            local playerCount
            playerCount = be:SYSgetPlayerNinzu()
            local local_6
            local_6 = g_fall0 + g_fall1 + g_fall2 + g_fall3
            if playerCount == local_6 then
                local local_7 = 0
                local_7 = be:MDLisLive("g_000bcaps", 0) + be:MDLisLive("g_000bcaps", 1) + be:MDLisLive("g_000bcaps", 2) + be:MDLisLive("g_000bcaps", 3)
                if local_7 == 0 then
                    be:sd("ENEMY", nil, -1, "OFCTRL")
                    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
                    local local_8
                    if g_fallPos == 41 then
                        local_8 = g_posTbl41
                    elseif g_fallPos == 42 then
                        local_8 = g_posTbl42
                    elseif g_fallPos == 43 then
                        local_8 = g_posTbl43
                    elseif g_fallPos == 44 then
                        local_8 = g_posTbl44
                    else
                        be:MsgBox("|WVæ¾É~Xª èÜ·Bg_fallPos=", g_fallPos)
                    end
                    be:DMsetSD("MATCTRL", nil, -1, "PAUSE", 0)
                    if g_fall0 == 1 then
                        generatePlayer(0, local_8[1], 30)
                        g_fall0 = 0
                    end
                    if g_fall1 == 1 then
                        generatePlayer(1, local_8[2], 30)
                        g_fall1 = 0
                    end
                    if g_fall2 == 1 then
                        generatePlayer(2, local_8[3], 30)
                        g_fall2 = 0
                    end
                    if g_fall3 == 1 then
                        generatePlayer(3, local_8[4], 30)
                        g_fall3 = 0
                    end
                    be:DMsetSD("MATCTRL", nil, -1, "RESTART", 40)
                    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 40)
                    be:sd("ENEMY", nil, -1, "ONCTRL", 90)
                    be:DMrun()
                end
            end
        end
    end
end
