mswk200371 = "TALKFONT02/font00/I<6>"
funcOneMessage(mswk200371)
mswk200372 = "TALKFONT02/font00/I<7>"
funcOneMessage(mswk200372)
mswk20038 = "TALKFONT02/font01/I<8>"
mswk20039 = "TALKFONT02/font02/I<9>"
mswk20040 = "TALKFONT02/font00/I<5>"
funcChoiceMessage(mswk20038, mswk20039)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest01.lua")
be:DMcase(1)
funcOneMessage(mswk20040)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
