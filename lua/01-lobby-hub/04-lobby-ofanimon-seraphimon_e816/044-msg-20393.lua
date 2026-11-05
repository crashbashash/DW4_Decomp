mswk20393 = "TALKFONT02/font01/I<0>"
mswk20394 = "TALKFONT02/font02/I<205>"
mswk20395 = "TALKFONT02/font00/I<226>"
funcChoiceMessage(mswk20393, mswk20394)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02111.lua")
be:DMcase(1)
funcOneMessage(mswk20395)
funcCloseMessage("talk", "n_digilff", "A[}E{[hEX^bt")
be:DMswtEnd()
be:DMrun()
