local local_0
local local_1
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        for species = 0, 15 do
            be:SYSctlShinka("SETSHINKA", playerIndex, species)
        end
    end
end
mswk80031 = "TALKFONT02/font00/I<87>"
funcOneMessage(mswk80031)
funcCloseMessage("talk", "n_digilff", "fWt")
be:DMrun()
