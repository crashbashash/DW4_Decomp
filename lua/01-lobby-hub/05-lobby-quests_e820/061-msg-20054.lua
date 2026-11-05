mswk20054 = "TALKFONT02/font01/I<19>"
mswk20055 = "TALKFONT02/font02/I<4>"
mswk20056 = "TALKFONT02/font00/I<20>"
funcChoiceMessage(mswk20054, mswk20055)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest03.lua")
be:DMcase(1)
funcOneMessage(mswk20056)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
