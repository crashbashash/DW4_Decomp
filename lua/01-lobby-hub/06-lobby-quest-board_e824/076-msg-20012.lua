mswk20012 = "TALKFONT02/font01/I<12>"
mswk20013 = "TALKFONT02/font02/I<13>"
mswk20014 = "TALKFONT02/font00/I<14>"
funcChoiceMessage(mswk20012, mswk20013)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bankshop.lua")
be:DMcase(1)
funcOneMessage(mswk20014)
funcCloseMessage("talk", "n_digilff", "fWt")
be:DMswtEnd()
be:DMrun()
