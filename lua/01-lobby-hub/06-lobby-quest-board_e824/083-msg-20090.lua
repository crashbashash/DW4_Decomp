mswk20090 = "TALKFONT02/font01/I<28>"
mswk20091 = "TALKFONT02/font02/I<29>"
mswk20092 = "TALKFONT02/font00/I<31>"
funcChoiceMessage(mswk20090, mswk20091)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML01031.lua")
be:DMcase(1)
funcOneMessage(mswk20092)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
