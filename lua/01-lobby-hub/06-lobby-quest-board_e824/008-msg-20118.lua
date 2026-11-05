mswk20118 = "TALKFONT02/font01/I<54>"
mswk20119 = "TALKFONT02/font02/I<55>"
mswk20120 = "TALKFONT02/font00/I<56>"
funcChoiceMessage(mswk20118, mswk20119)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML01042.lua")
be:DMcase(1)
funcOneMessage(mswk20120)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
