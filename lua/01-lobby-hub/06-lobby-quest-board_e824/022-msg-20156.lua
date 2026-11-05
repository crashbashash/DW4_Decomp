mswk20156 = "TALKFONT02/font01/I<94>"
mswk20157 = "TALKFONT02/font02/I<76>"
mswk20158 = "TALKFONT02/font00/I<95>"
funcChoiceMessage(mswk20156, mswk20157)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest08stop.lua")
be:DMcase(1)
funcOneMessage(mswk20158)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
