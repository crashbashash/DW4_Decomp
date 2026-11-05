mswk20321 = "TALKFONT02/font01/I<0>"
mswk20322 = "TALKFONT02/font02/I<1>"
mswk20323 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20321, mswk20322)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02069.lua")
be:DMcase(1)
funcOneMessage(mswk20323)
funcCloseMessage("talk", "n_digilfm", "ogVXeEX^bt")
be:DMswtEnd()
be:DMrun()
