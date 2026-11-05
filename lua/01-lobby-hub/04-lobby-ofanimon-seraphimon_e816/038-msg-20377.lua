mswk20377 = "TALKFONT02/font01/I<0>"
mswk20378 = "TALKFONT02/font02/I<205>"
mswk20379 = "TALKFONT02/font00/I<206>"
funcChoiceMessage(mswk20377, mswk20378)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02093.lua")
be:DMcase(1)
funcOneMessage(mswk20379)
funcCloseMessage("talk", "n_digilff", "Xe[^XEX^bt")
be:DMswtEnd()
be:DMrun()
