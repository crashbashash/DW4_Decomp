mswk20000 = "TALKFONT02/font01/I<0>"
mswk20001 = "TALKFONT02/font02/I<1>"
mswk20002 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20000, mswk20001)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("cardshop.lua")
be:DMcase(1)
funcOneMessage(mswk20002)
funcCloseMessage("talk", "n_digilff", "fWt")
be:DMswtEnd()
be:DMrun()
