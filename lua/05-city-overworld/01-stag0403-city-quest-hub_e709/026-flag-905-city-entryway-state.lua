be:FLGset(905, 0)
if be:SYSctlFlagFolder("IS", 9) == 1 and be:SYSctlFlagFolder("IS", 10) == 1 then
    be:FLGset(905, 1)
end
if be:FLGisOn(905) == 0 then
    if be:MATisAllPlayer() == 1 and be:DMgetCount() <= 0 then
        if be:DMgetCount() == -1 then
            be:sd("SUBWND", nil, -1, "REMOVE")
            be:DMchkSD("SUBWND", nil, -1, "ISRUN", "!=0")
        end
        g_messPlayerNo = be:MATgetPlayerNo()
        local hp = be:SYSctlPlayer("HP", "GETHP", g_messPlayerNo, 0)
        if hp ~= 0 then
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
            be:sd("PLAYER", nil, -1, "OFCTRL")
            be:sd("ENEMY", nil, -1, "OFCTRL")
            funcOpenMessage("mess")
            mswk62004 = "TALKFONT01/font00/I<17>"
            funcOneMessage(mswk62004)
            funcCloseMessage("mess")
            be:DMrun()
        end
    end
elseif be:FLGisOn(905) == 1 then
    if be:MATisAllPlayer() == 1 then
        be:sd("MODELCTRL", "g_entrywayz04", 0, "SQ_SWON02")
        if be:DMgetCount() == 0 then
            g_messPlayerNo = be:MATgetPlayerNo()
            local hp = be:SYSctlPlayer("HP", "GETHP", g_messPlayerNo, 0)
            if hp ~= 0 then
                be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
                be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
                be:sd("PLAYER", nil, -1, "OFCTRL")
                be:sd("ENEMY", nil, -1, "OFCTRL")
                funcOpenMessage("mess")
                mswk62005 = "TALKFONT01/font01/I<18>"
                mswk62006 = "TALKFONT01/font02/I<19>"
                funcChoiceMessage(mswk62005, mswk62006)
                be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
                be:DMcase(0)
                be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
                be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
                be:DMsetSD("MODELCTRL", "g_entrywayz04", 0, "SQ_SWON03")
                local local_1
                local offset = 30
                be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "AM_MACHI/F<1.0>/F<0.0>/F<5>")
                be:DMsetSD("SOUND", nil, -1, "ENVSTOP", "AM_MACHI", 6)
                for playerIndex = 0, 3 do
                    if be:SYSisJoinPlayer(playerIndex) == 1 then
                        be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_EXIT", offset)
                        offset = offset + 30
                    end
                end
                be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "SHIP_DEMO", 7)
                be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "SHIP_DEMO", 8)
                be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "starship00", 40)
                be:DMsetSD("MODELCTRL", "r_starshipz041", 0, "SQ_GO", 40)
                be:DMsetSD("MODELCTRL", "g_starshipz04", 0, "SQ_WAIT00", 100)
                be:DMsetSD("MODELCTRL", "g_ringz04", 0, "SQ_SWON", 160)
                be:DMsetSD("MODELCTRL", "g_ringz04", 1, "SQ_SWON", 160)
                be:DMsetSD("MODELCTRL", "g_ringz04", 2, "SQ_SWON", 160)
                be:DMsetSD("MODELCTRL", "g_ringz04", 3, "SQ_SWON", 160)
                be:DMsetSD("MODELCTRL", "g_starshipz04", 0, "SQ_SWON", 200)
                be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT60", 1100)
                be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
                be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
                be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 1)
                be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stag0403", 1)
                be:DMcase(1)
                funcCloseMessage("mess")
                be:DMswtEnd()
                be:DMrun()
            end
        end
    else
        be:sd("MODELCTRL", "g_entrywayz04", 0, "SQ_SWOF01")
    end
end
