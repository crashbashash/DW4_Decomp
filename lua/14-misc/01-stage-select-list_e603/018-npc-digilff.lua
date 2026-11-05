funcOpenMessage("talk", "n_digilff", "fWt")
mswk80005 = "TALKFONT02/font00/I<48>"
funcOneMessage(mswk80005)
mswk80006 = "TALKFONT02/font01/I<49>"
mswk80007 = "TALKFONT02/font02/I<50>"
funcChoiceMessage(mswk80006, mswk80007)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("b0001001.lua")
be:DMcase(1)
funcCloseMessage("talk", "n_digilff", "fWt")
be:DMswtEnd()
be:DMrun()
