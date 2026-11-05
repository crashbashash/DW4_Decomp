mswk20191 = "TALKFONT02/font01/I<0>"
mswk20192 = "TALKFONT02/font02/I<1>"
mswk20193 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20191, mswk20192)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02013.lua")
be:DMcase(1)
funcOneMessage(mswk20193)
funcCloseMessage("talk", "n_digilff", "goloX^bt")
be:DMswtEnd()
be:DMrun()
