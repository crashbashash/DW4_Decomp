for local_1 = 0, 3 do
    if be:SYSisJoinPlayer(local_1) == 1 and be:MATgetPlayerMatStat(local_1) == 2 then
        be:sd("PLAYER", nil, local_1, "SETCONVEYOR", "I<0>")
    end
end
