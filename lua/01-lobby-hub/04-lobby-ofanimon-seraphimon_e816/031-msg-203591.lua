mswk203591 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk203591)
mswk20360 = "TALKFONT02/font01/I<0>"
mswk20361 = "TALKFONT02/font02/I<1>"
mswk20362 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20360, mswk20361)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02082.lua")
be:DMcase(1)
funcOneMessage(mswk20362)
funcCloseMessage("talk", "n_digilff", "loUEX^bt")
be:DMswtEnd()
be:DMrun()
