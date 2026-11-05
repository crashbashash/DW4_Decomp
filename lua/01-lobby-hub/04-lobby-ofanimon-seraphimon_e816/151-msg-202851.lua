mswk202851 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk202851)
mswk20286 = "TALKFONT02/font01/I<0>"
mswk20287 = "TALKFONT02/font02/I<1>"
mswk20288 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20286, mswk20287)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02050.lua")
be:DMcase(1)
funcOneMessage(mswk20288)
funcCloseMessage("talk", "n_digilfm", "fW{EX^bt")
be:DMswtEnd()
be:DMrun()
