mswk20071 = "TALKFONT02/font01/I<32>"
mswk20072 = "TALKFONT02/font02/I<11>"
mswk20073 = "TALKFONT02/font00/I<33>"
funcChoiceMessage(mswk20071, mswk20072)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest04stop.lua")
be:DMcase(1)
funcOneMessage(mswk20073)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
