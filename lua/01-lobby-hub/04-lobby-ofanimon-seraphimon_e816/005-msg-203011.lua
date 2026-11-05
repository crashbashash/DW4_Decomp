mswk203011 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk203011)
mswk20302 = "TALKFONT02/font01/I<0>"
mswk20303 = "TALKFONT02/font02/I<1>"
mswk20304 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20302, mswk20303)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02055.lua")
be:DMcase(1)
funcOneMessage(mswk20304)
funcCloseMessage("talk", "n_digilff", "»¤ÑX^bt")
be:DMswtEnd()
be:DMrun()
