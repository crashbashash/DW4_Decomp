mswk20021 = "TALKFONT02/font01/I<3>"
mswk20022 = "TALKFONT02/font02/I<4>"
mswk20023 = "TALKFONT02/font00/I<5>"
funcChoiceMessage(mswk20021, mswk20022)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("diskshop.lua")
be:DMcase(1)
funcOneMessage(mswk20023)
funcCloseMessage("talk", "n_digilff", "fWt")
be:DMswtEnd()
be:DMrun()
