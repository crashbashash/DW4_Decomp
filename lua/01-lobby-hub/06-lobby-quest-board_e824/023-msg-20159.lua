mswk20159 = "TALKFONT02/font01/I<96>"
mswk20160 = "TALKFONT02/font02/I<97>"
mswk20161 = "TALKFONT02/font00/I<98>"
funcChoiceMessage(mswk20159, mswk20160)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("questf3.lua")
be:DMcase(1)
funcOneMessage(mswk20161)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
