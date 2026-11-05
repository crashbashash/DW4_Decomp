mswk201751 = "TALKFONT02/font00/I<14>"
funcOneMessage(mswk201751)
mswk20176 = "TALKFONT02/font01/I<0>"
mswk20177 = "TALKFONT02/font02/I<1>"
mswk20178 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20176, mswk20177)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02002.lua")
be:DMcase(1)
funcOneMessage(mswk20178)
funcCloseMessage("talk", "n_digilfm", "Z[u[hEX^bt")
be:DMswtEnd()
be:DMrun()
