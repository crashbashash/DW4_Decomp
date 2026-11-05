mswk203731 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk203731)
mswk20374 = "TALKFONT02/font01/I<0>"
mswk20375 = "TALKFONT02/font02/I<1>"
mswk20376 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20374, mswk20375)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02087.lua")
be:DMcase(1)
funcOneMessage(mswk20376)
funcCloseMessage("talk", "n_digilff", "loUp[^EX^bt")
be:DMswtEnd()
be:DMrun()
