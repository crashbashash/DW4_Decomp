mswk202291 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk202291)
mswk20230 = "TALKFONT02/font01/I<0>"
mswk20231 = "TALKFONT02/font02/I<1>"
mswk20232 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20230, mswk20231)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02026.lua")
be:DMcase(1)
funcOneMessage(mswk20232)
funcCloseMessage("talk", "n_digilfm", "ACREX^bt")
be:DMswtEnd()
be:DMrun()
