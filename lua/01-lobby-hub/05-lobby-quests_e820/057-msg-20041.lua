mswk20041 = "TALKFONT02/font01/I<10>"
mswk20042 = "TALKFONT02/font02/I<11>"
mswk20043 = "TALKFONT02/font00/I<12>"
funcChoiceMessage(mswk20041, mswk20042)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest01stop.lua")
be:DMcase(1)
funcOneMessage(mswk20043)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
