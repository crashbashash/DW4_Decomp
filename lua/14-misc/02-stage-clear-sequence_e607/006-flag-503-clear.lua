be:sd("NDMWPANEL", nil, -1, "NOGATEDISK", "I<1>")
be:FLGset(503, 0)
be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "SQ_CLOSE")
be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "!=0")
local local_0
local offset = 40
be:DMsetSD("MODELCTRL", "i_stpnl00", 0, "SQ_OPEN")
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        be:DMsetSD("MODELCTRL", "i_stpnl01", playerIndex, "SQ_OPEN")
        be:DMsetSD("MODELCTRL", "i_stpnl02", playerIndex, be:SYSgetPlayerName(playerIndex))
        be:DMsetSD("MODELCTRL", "i_stpnl03", playerIndex, "SQ_OPENWN")
        be:DMsetSD("MODELCTRL", "i_stpnl04", playerIndex, "SQ_OPENWN")
    end
end
be:DMsetSD("MATCTRL", nil, -1, "PAUSE")
be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT")
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_EXIT", offset)
        offset = offset + 20
    end
end
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", offset)
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_STCHANGELP", "==0")
be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 10)
be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stag0001", 10)
be:DMrun()
