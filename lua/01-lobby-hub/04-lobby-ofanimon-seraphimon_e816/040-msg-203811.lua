mswk203811 = "TALKFONT02/font00/I<216>"
funcOneMessage(mswk203811)
mswk20382 = "TALKFONT02/font01/I<0>"
mswk20383 = "TALKFONT02/font02/I<205>"
mswk20384 = "TALKFONT02/font00/I<217>"
funcChoiceMessage(mswk20382, mswk20383)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02093.lua")
be:DMcase(1)
funcOneMessage(mswk20384)
funcCloseMessage("talk", "n_digilff", "Xe[^XEX^bt")
be:DMswtEnd()
be:DMrun()
