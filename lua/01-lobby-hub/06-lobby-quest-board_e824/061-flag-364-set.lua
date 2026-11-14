be:FLGset(364, 1)
local local_0
local count = 0
local count2 = 0
local local_3 = 80
be:sd("PLAYER", nil, -1, "OFCTRL")
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        count2 = count2 + 1
        local maxHp = be:SYSctlPlayer("HP", "GETMHP", playerIndex, 0)
        local maxMp = be:SYSctlPlayer("MP", "GETMMP", playerIndex, 0)
        be:sd("GAMERAM", nil, 0, "ADDHP", "I<" .. playerIndex .. ">/I<" .. maxHp .. ">")
        be:sd("GAMERAM", nil, 0, "ADDMP", "I<" .. playerIndex .. ">/I<" .. maxMp .. ">")
    end
end
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_CLOSE", "!=0")
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 and be:SYSgetPlayerDigimon(playerIndex) ~= be:COUNTERget(playerIndex + 8) then
        count = count + 1
    end
end
if count == 0 then
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
if count == 0 then
    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<3>", 30)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML12", 30)
else
    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 30)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML14", 30)
end
be:DMrun()
