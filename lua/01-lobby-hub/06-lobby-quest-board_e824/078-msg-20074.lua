mswk20074 = "TALKFONT02/font01/I<18>"
mswk20075 = "TALKFONT02/font02/I<19>"
mswk20076 = "TALKFONT02/font00/I<20>"
funcChoiceMessage(mswk20074, mswk20075)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest05.lua")
be:DMcase(1)
funcOneMessage(mswk20076)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
