mswk20165 = "TALKFONT02/font01/I<0>"
mswk20166 = "TALKFONT02/font02/I<1>"
mswk20167 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20165, mswk20166)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02002.lua")
be:DMcase(1)
funcOneMessage(mswk20167)
funcCloseMessage("talk", "n_digilfm", "Z[u[hEX^bt")
be:DMswtEnd()
be:DMrun()
