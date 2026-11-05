mswk20153 = "TALKFONT02/font01/I<94>"
mswk20154 = "TALKFONT02/font02/I<76>"
mswk20155 = "TALKFONT02/font00/I<95>"
funcChoiceMessage(mswk20153, mswk20154)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest08stop.lua")
be:DMcase(1)
funcOneMessage(mswk20155)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
