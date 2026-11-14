if be:DMgetCount() == -1 then
    be:sd("SUBWND", nil, -1, "REMOVE")
    be:DMchkSD("SUBWND", nil, -1, "ISRUN", "!=0")
end
be:sd("PLAYER", nil, -1, "OFCTRL")
be:sd("ENEMY", nil, -1, "OFCTRL")
be:sd("PLAYER", nil, -1, "ALLCLEARSTATUS")
if g_GateOn == 1 then
    be:SYSsetGateStage(g_GateStage, g_GatePos)
else
    be:SYSsetGateStage("GateOff", -1)
end
local local_0
local offset = 40
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_EXIT", offset)
        offset = offset + 20
    end
end
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", offset + 40)
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "!=0")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_STCHANGELP", "==0")
be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<3>", 10)
be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML11", 10)
be:DMrun()
