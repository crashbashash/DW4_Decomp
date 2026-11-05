mswk20130 = "TALKFONT02/font01/I<69>"
mswk20131 = "TALKFONT02/font02/I<70>"
mswk20132 = "TALKFONT02/font00/I<71>"
funcChoiceMessage(mswk20130, mswk20131)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML01046.lua")
be:DMcase(1)
funcOneMessage(mswk20132)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
