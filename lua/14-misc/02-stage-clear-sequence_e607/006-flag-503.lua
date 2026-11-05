be:sd("NDMWPANEL", nil, -1, "NOGATEDISK", "I<1>")
be:FLGset(503, 0)
be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "!=0")
be:DMsetSD("MODELCTRL", "i_stpnl00", 0, "SQ_OPEN")
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
be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stag0001", 10)
be:DMrun()
