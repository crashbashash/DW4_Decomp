mswk20351 = "TALKFONT02/font01/I<0>"
mswk20352 = "TALKFONT02/font02/I<1>"
mswk20353 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20351, mswk20352)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02082.lua")
be:DMcase(1)
funcOneMessage(mswk20353)
funcCloseMessage("talk", "n_digilff", "loUEX^bt")
be:DMswtEnd()
be:DMrun()
