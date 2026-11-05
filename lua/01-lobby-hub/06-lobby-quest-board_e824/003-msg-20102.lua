mswk20102 = "TALKFONT02/font01/I<41>"
mswk20103 = "TALKFONT02/font02/I<42>"
mswk20104 = "TALKFONT02/font00/I<43>"
funcChoiceMessage(mswk20102, mswk20103)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest06stop.lua")
be:DMcase(1)
funcOneMessage(mswk20104)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
