mswk20096 = "TALKFONT02/font01/I<37>"
mswk20097 = "TALKFONT02/font02/I<38>"
mswk20098 = "TALKFONT02/font00/I<39>"
funcChoiceMessage(mswk20096, mswk20097)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest06.lua")
be:DMcase(1)
funcOneMessage(mswk20098)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
