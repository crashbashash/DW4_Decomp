mswk20221 = "TALKFONT02/font01/I<0>"
mswk20222 = "TALKFONT02/font02/I<1>"
mswk20223 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20221, mswk20222)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02026.lua")
be:DMcase(1)
funcOneMessage(mswk20223)
funcCloseMessage("talk", "n_digilfm", "ACREX^bt")
be:DMswtEnd()
be:DMrun()
