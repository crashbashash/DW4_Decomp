mswk202011 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk202011)
mswk20202 = "TALKFONT02/font01/I<0>"
mswk20203 = "TALKFONT02/font02/I<1>"
mswk20204 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20202, mswk20203)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02013.lua")
be:DMcase(1)
funcOneMessage(mswk20204)
funcCloseMessage("talk", "n_digilff", "goloX^bt")
be:DMswtEnd()
be:DMrun()
