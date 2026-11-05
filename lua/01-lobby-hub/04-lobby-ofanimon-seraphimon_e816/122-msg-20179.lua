mswk20179 = "TALKFONT02/font01/I<0>"
mswk20180 = "TALKFONT02/font02/I<1>"
mswk20181 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20179, mswk20180)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02008.lua")
be:DMcase(1)
funcOneMessage(mswk20181)
funcCloseMessage("talk", "n_digilfm", "Q[gEX^bt")
be:DMswtEnd()
be:DMrun()
