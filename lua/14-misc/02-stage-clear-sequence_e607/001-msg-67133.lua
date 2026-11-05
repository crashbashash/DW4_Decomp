be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67133)
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT02/font01/SET", 10)
be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67134)
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT02/font02/SET", 10)
be:DMsetSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GENERATE", "NOCANCEL/I<2>/V<80,-2,0>", 10)
be:DMchkSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "ISEND", "!=0")
be:DMchkSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "ISEND", "==0")
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT02/font01/CLR")
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT02/font02/CLR")
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
be:DMcase(1)
be:DMsetLua("restart.lua")
be:DMswtEnd()
be:DMrun()
