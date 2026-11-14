local local_0 = 105
local local_1 = local_0 * local_0 * local_0 + 140 * (local_0 * local_0) + 200 * local_0
local local_2
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        be:SYSctlPlayer("EXP", "SET", playerIndex, local_1)
    end
end
funcOneMessage(mswk80037)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMrun()
