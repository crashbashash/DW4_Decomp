mswk20385 = "TALKFONT02/font01/I<0>"
mswk20386 = "TALKFONT02/font02/I<205>"
mswk20387 = "TALKFONT02/font00/I<218>"
funcChoiceMessage(mswk20385, mswk20386)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02107.lua")
be:DMcase(1)
funcOneMessage(mswk20387)
funcCloseMessage("talk", "n_digilfm", "EF|EjbgEX^bt")
be:DMswtEnd()
be:DMrun()
