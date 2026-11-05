mswk20233 = "TALKFONT02/font01/I<0>"
mswk20234 = "TALKFONT02/font02/I<1>"
mswk20235 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20233, mswk20234)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02031.lua")
be:DMcase(1)
funcOneMessage(mswk20235)
funcCloseMessage("talk", "n_digilfm", "xgoloX^bt")
be:DMswtEnd()
be:DMrun()
