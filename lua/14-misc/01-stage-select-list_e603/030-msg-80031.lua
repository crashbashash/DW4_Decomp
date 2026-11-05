for local_2 = 0, 3 do
    if be:SYSisJoinPlayer(local_2) == 1 then
        for local_5 = 0, 15 do
            be:SYSctlShinka("SETSHINKA", local_2, local_5)
        end
    end
end
mswk80031 = "TALKFONT02/font00/I<87>"
funcOneMessage(mswk80031)
funcCloseMessage("talk", "n_digilff", "fWt")
be:DMrun()
