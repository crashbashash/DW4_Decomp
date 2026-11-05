mswk200471 = "TALKFONT02/font00/I<15>"
funcOneMessage(mswk200471)
mswk200472 = "TALKFONT02/font00/I<16>"
funcOneMessage(mswk200472)
mswk20048 = "TALKFONT02/font01/I<8>"
mswk20049 = "TALKFONT02/font02/I<9>"
mswk20050 = "TALKFONT02/font00/I<14>"
funcChoiceMessage(mswk20048, mswk20049)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest02.lua")
be:DMcase(1)
funcOneMessage(mswk20050)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
