mswk20003 = "TALKFONT02/font01/I<3>"
mswk20004 = "TALKFONT02/font02/I<4>"
mswk20005 = "TALKFONT02/font00/I<5>"
funcChoiceMessage(mswk20003, mswk20004)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("saveshop.lua")
be:DMcase(1)
funcOneMessage(mswk20005)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
