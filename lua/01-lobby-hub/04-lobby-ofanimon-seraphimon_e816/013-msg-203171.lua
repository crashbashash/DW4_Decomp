mswk203171 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk203171)
mswk20318 = "TALKFONT02/font01/I<0>"
mswk20319 = "TALKFONT02/font02/I<1>"
mswk20320 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20318, mswk20319)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02062.lua")
be:DMcase(1)
funcOneMessage(mswk20320)
funcCloseMessage("talk", "n_digilff", "AreBE`bv»¤ÑX^bt")
be:DMswtEnd()
be:DMrun()
