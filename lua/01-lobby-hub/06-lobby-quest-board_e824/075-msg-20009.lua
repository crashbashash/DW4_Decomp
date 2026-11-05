mswk20009 = "TALKFONT02/font01/I<9>"
mswk20010 = "TALKFONT02/font02/I<10>"
mswk20011 = "TALKFONT02/font00/I<11>"
funcChoiceMessage(mswk20009, mswk20010)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("digilabshop.lua")
be:DMcase(1)
funcOneMessage(mswk20011)
funcCloseMessage("talk", "n_digilff", "fWt")
be:DMswtEnd()
be:DMrun()
