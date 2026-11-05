mswk20137 = "TALKFONT02/font01/I<69>"
mswk20138 = "TALKFONT02/font02/I<76>"
mswk20139 = "TALKFONT02/font00/I<77>"
funcChoiceMessage(mswk20137, mswk20138)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest07stop2.lua")
be:DMcase(1)
funcOneMessage(mswk20139)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
