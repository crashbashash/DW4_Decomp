mswk20034 = "TALKFONT02/font01/I<3>"
mswk20035 = "TALKFONT02/font02/I<4>"
mswk20036 = "TALKFONT02/font00/I<5>"
funcChoiceMessage(mswk20034, mswk20035)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest01.lua")
be:DMcase(1)
funcOneMessage(mswk20036)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
