mswk20064 = "TALKFONT02/font01/I<25>"
mswk20065 = "TALKFONT02/font02/I<26>"
mswk20066 = "TALKFONT02/font00/I<27>"
funcChoiceMessage(mswk20064, mswk20065)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest04.lua")
be:DMcase(1)
funcOneMessage(mswk20066)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
