mswk203971 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk203971)
mswk20398 = "TALKFONT02/font01/I<0>"
mswk20399 = "TALKFONT02/font02/I<205>"
mswk20400 = "TALKFONT02/font00/I<226>"
funcChoiceMessage(mswk20398, mswk20399)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02111.lua")
be:DMcase(1)
funcOneMessage(mswk20400)
funcCloseMessage("talk", "n_digilff", "A[}E{[hEX^bt")
be:DMswtEnd()
be:DMrun()
