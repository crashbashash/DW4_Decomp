if be:MATisAllPlayer() == 1 and be:DMgetCount() == 0 then
    g_messPlayerNo = 0
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    mswk67131 = "TALKFONT02/font01/I<50>"
    mswk67132 = "TALKFONT02/font02/I<51>"
    mswk67133 = "TALKFONT02/font01/I<52>"
    mswk67134 = "TALKFONT02/font02/I<53>"
    mswk67135 = "TALKFONT05/font00/I<54>"
    be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "==0")
    be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
    if be:COUNTERget(7) == 10 then
        be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67131)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT02/font01/SET", 10)
        be:DMsetSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GENERATE", "NOCANCEL/I<1>/V<80,-2,0>", 10)
        be:DMchkSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "ISEND", "!=0")
        be:DMchkSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "ISEND", "==0")
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT02/font01/CLR")
        be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
        be:DMcase(0)
        be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
        be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "!=0")
        be:DMsetSD("NDMWPANEL", nil, -1, "NOGATEDISK", "I<0>")
        for local_2 = 0, 3 do
            if be:SYSisJoinPlayer(local_2) == 1 then
                be:DMsetSD("MODELCTRL", "i_stpnl01", local_2, "SQ_OPEN")
                be:DMsetSD("MODELCTRL", "i_stpnl02", local_2, be:SYSgetPlayerName(local_2))
                be:DMsetSD("MODELCTRL", "i_stpnl03", local_2, "SQ_OPENWN")
                be:DMsetSD("MODELCTRL", "i_stpnl04", local_2, "SQ_OPENWN")
            end
        end
        be:DMsetSD("MATCTRL", nil, -1, "PAUSE")
        be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT")
        for local_2 = 0, 3 do
            if be:SYSisJoinPlayer(local_2) == 1 then
                be:DMsetSD("PLAYER", be:SYSgetPlayerName(local_2), local_2, "SQ_EXIT", local_1)
                local_1 = local_1 + 20
            end
        end
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", local_1)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_STCHANGELP", "==0")
        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 10)
        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stag0101", 10)
        be:DMswtEnd()
        be:DMrun()
    else
        be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67131)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT02/font01/SET", 10)
        be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67132)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT02/font02/SET", 10)
        be:DMsetSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GENERATE", "NOCANCEL/I<2>/V<80,-2,0>", 10)
        be:DMchkSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "ISEND", "!=0")
        be:DMchkSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "ISEND", "==0")
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT02/font01/CLR")
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT02/font02/CLR")
        be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
        be:DMcase(0)
        be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67135)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
        be:DMsetSD("SELECTCTRL", "i_messky", g_messPlayerNo, "GENERATE")
        be:DMchkSD("SELECTCTRL", "i_messky", g_messPlayerNo, "ISEND", "==0")
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
        be:DMsetLua("stchg01.lua")
        be:DMcase(1)
        be:DMsetLua("restart.lua")
        be:DMswtEnd()
        be:DMrun()
    end
end
