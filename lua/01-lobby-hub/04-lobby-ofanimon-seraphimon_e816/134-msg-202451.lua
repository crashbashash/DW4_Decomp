mswk202451 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk202451)
mswk20246 = "TALKFONT02/font01/I<0>"
mswk20247 = "TALKFONT02/font02/I<1>"
mswk20248 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20246, mswk20247)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02031.lua")
be:DMcase(1)
funcOneMessage(mswk20248)
funcCloseMessage("talk", "n_digilfm", "xgoloX^bt")
be:DMswtEnd()
be:DMrun()
