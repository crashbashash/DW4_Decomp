mswk20289 = "TALKFONT02/font01/I<0>"
mswk20290 = "TALKFONT02/font02/I<1>"
mswk20291 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20289, mswk20290)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02055.lua")
be:DMcase(1)
funcOneMessage(mswk20291)
funcCloseMessage("talk", "n_digilff", "»¤ÑX^bt")
be:DMswtEnd()
be:DMrun()
