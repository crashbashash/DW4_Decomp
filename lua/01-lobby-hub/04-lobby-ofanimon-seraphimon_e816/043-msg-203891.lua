mswk203891 = "TALKFONT02/font00/I<225>"
funcOneMessage(mswk203891)
mswk20390 = "TALKFONT02/font01/I<0>"
mswk20391 = "TALKFONT02/font02/I<205>"
mswk20392 = "TALKFONT02/font00/I<218>"
funcChoiceMessage(mswk20390, mswk20391)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02107.lua")
be:DMcase(1)
funcOneMessage(mswk20392)
funcCloseMessage("talk", "n_digilfm", "EF|EjbgEX^bt")
be:DMswtEnd()
be:DMrun()
