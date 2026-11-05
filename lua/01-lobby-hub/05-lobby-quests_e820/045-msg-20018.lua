mswk20018 = "TALKFONT02/font01/I<0>"
mswk20019 = "TALKFONT02/font02/I<1>"
mswk20020 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20018, mswk20019)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("callshop.lua")
be:DMcase(1)
funcOneMessage(mswk20020)
funcCloseMessage("talk", "n_digilff", "fWt")
be:DMswtEnd()
be:DMrun()
