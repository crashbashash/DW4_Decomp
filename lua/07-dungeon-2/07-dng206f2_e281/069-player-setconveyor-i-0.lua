local local_0
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 and be:MATgetPlayerMatStat(playerIndex) == 2 then
        be:sd("PLAYER", nil, playerIndex, "SETCONVEYOR", "I<0>")
    end
end
