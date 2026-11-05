mswk20305 = "TALKFONT02/font01/I<0>"
mswk20306 = "TALKFONT02/font02/I<1>"
mswk20307 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20305, mswk20306)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02062.lua")
be:DMcase(1)
funcOneMessage(mswk20307)
funcCloseMessage("talk", "n_digilff", "AreBE`bv»¤ÑX^bt")
be:DMswtEnd()
be:DMrun()
