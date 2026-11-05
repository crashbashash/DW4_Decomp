mswk20335 = "TALKFONT02/font01/I<0>"
mswk20336 = "TALKFONT02/font02/I<1>"
mswk20337 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20335, mswk20336)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02075.lua")
be:DMcase(1)
funcOneMessage(mswk20337)
funcCloseMessage("talk", "n_digilfm", "XLVXeEX^bt")
be:DMswtEnd()
be:DMrun()
