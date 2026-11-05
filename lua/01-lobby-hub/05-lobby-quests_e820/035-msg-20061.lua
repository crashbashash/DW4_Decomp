mswk20061 = "TALKFONT02/font01/I<23>"
mswk20062 = "TALKFONT02/font02/I<11>"
mswk20063 = "TALKFONT02/font00/I<24>"
funcChoiceMessage(mswk20061, mswk20062)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest03stop.lua")
be:DMcase(1)
funcOneMessage(mswk20063)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
