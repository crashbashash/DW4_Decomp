mswk200861 = "TALKFONT02/font00/I<30>"
funcOneMessage(mswk200861)
mswk20087 = "TALKFONT02/font01/I<25>"
mswk20088 = "TALKFONT02/font02/I<26>"
mswk20089 = "TALKFONT02/font00/I<27>"
funcChoiceMessage(mswk20087, mswk20088)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest05stop.lua")
be:DMcase(1)
funcOneMessage(mswk20089)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
