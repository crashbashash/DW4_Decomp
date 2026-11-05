mswk20006 = "TALKFONT02/font01/I<6>"
mswk20007 = "TALKFONT02/font02/I<7>"
mswk20008 = "TALKFONT02/font00/I<8>"
funcChoiceMessage(mswk20006, mswk20007)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("xdatashop.lua")
be:DMcase(1)
funcOneMessage(mswk20008)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
