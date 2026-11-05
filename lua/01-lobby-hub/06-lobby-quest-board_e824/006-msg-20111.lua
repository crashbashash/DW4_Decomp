mswk20111 = "TALKFONT02/font01/I<48>"
mswk20112 = "TALKFONT02/font02/I<49>"
mswk20113 = "TALKFONT02/font00/I<50>"
funcChoiceMessage(mswk20111, mswk20112)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML01039.lua")
be:DMcase(1)
funcOneMessage(mswk20113)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
