if be:MATisPlayer() == 1 then
    for local_2 = 0, 3 do
        if be:MATisRidePlayer(local_2) == 1 then
            be:sd("GAMERAM", nil, 0, "ADDHP", "I<" .. local_2 .. ">/I<-99999>")
            if local_2 == 0 then
                g_fall0 = 1
            elseif local_2 == 1 then
                g_fall1 = 1
            elseif local_2 == 2 then
                g_fall2 = 1
            else
                g_fall3 = 1
            end
            be:sd("PLAYER", nil, local_2, "REMOVE")
            local_5 = be:SYSgetPlayerNinzu()
            local_6 = g_fall0 + g_fall1 + g_fall2 + g_fall3
            if local_5 == local_6 then
                local_7 = be:MDLisLive("g_000bcaps", 0) + be:MDLisLive("g_000bcaps", 1) + be:MDLisLive("g_000bcaps", 2) + be:MDLisLive("g_000bcaps", 3)
                if local_7 == 0 then
                    be:sd("ENEMY", nil, -1, "OFCTRL")
                    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30")
                    if g_fallPos == 0 then
                        local_8 = g_posTbl00
                    else
                        be:MsgBox("|WVæ¾É~Xª èÜ·Bg_fallPos=", g_fallPos)
                    end
                    be:DMsetSD("MATCTRL", nil, -1, "PAUSE", 0)
                    if g_fall0 == 1 then
                        local_0(0, local_8[1], 30)
                        g_fall0 = 0
                    end
                    if g_fall1 == 1 then
                        local_0(1, local_8[2], 30)
                        g_fall1 = 0
                    end
                    if g_fall2 == 1 then
                        local_0(2, local_8[3], 30)
                        g_fall2 = 0
                    end
                    if g_fall3 == 1 then
                        local_0(3, local_8[4], 30)
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
