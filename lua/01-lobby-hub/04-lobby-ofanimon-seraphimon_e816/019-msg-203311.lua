mswk203311 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk203311)
mswk20332 = "TALKFONT02/font01/I<0>"
mswk20333 = "TALKFONT02/font02/I<1>"
mswk20334 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20332, mswk20333)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02069.lua")
be:DMcase(1)
funcOneMessage(mswk20334)
funcCloseMessage("talk", "n_digilfm", "ogVXeEX^bt")
be:DMswtEnd()
be:DMrun()
