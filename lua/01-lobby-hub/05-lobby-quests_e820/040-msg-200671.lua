mswk200671 = "TALKFONT02/font00/I<28>"
funcOneMessage(mswk200671)
mswk200672 = "TALKFONT02/font00/I<29>"
funcOneMessage(mswk200672)
mswk20068 = "TALKFONT02/font01/I<30>"
mswk20069 = "TALKFONT02/font02/I<31>"
mswk20070 = "TALKFONT02/font00/I<27>"
funcChoiceMessage(mswk20068, mswk20069)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest04.lua")
be:DMcase(1)
funcOneMessage(mswk20070)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
