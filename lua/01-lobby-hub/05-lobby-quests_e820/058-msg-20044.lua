mswk20044 = "TALKFONT02/font01/I<13>"
mswk20045 = "TALKFONT02/font02/I<4>"
mswk20046 = "TALKFONT02/font00/I<14>"
funcChoiceMessage(mswk20044, mswk20045)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest02.lua")
be:DMcase(1)
funcOneMessage(mswk20046)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
