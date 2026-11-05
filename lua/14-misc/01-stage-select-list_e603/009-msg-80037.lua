for local_3 = 0, 3 do
    if be:SYSisJoinPlayer(local_3) == 1 then
        be:SYSctlPlayer("EXP", "SET", local_3, local_1)
    end
end
funcOneMessage(mswk80037)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMrun()
