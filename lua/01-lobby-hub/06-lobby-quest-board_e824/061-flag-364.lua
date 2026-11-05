be:FLGset(364, 1)
be:sd("PLAYER", nil, -1, "OFCTRL")
for local_4 = 0, 3 do
    if be:SYSisJoinPlayer(local_4) == 1 then
        local_2 = local_2 + 1
        be:sd("GAMERAM", nil, 0, "ADDHP", "I<" .. local_4 .. ">/I<" .. local_7 .. ">")
        be:sd("GAMERAM", nil, 0, "ADDMP", "I<" .. local_4 .. ">/I<" .. local_8 .. ">")
    end
end
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_CLOSE", "!=0")
for local_4 = 0, 3 do
    if be:SYSisJoinPlayer(local_4) == 1 and be:SYSgetPlayerDigimon(local_4) ~= be:COUNTERget(local_4 + 8) then
        local_1 = local_1 + 1
    end
end
if local_1 == 0 then
    if be:FLGisOn(3) == 0 then
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY")
    elseif be:FLGisOn(3) == 1 then
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_OFNI2")
    end
    if be:FLGisOn(3) == 0 then
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY")
    elseif be:FLGisOn(3) == 1 then
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_HURRY")
    end
end
if local_1 == 0 then
    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<3>", 30)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML12", 30)
else
    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 30)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML14", 30)
end
be:DMrun()
