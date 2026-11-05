mswk201051 = "TALKFONT02/font00/I<44>"
funcOneMessage(mswk201051)
mswk20106 = "TALKFONT02/font01/I<41>"
mswk20107 = "TALKFONT02/font02/I<42>"
mswk20108 = "TALKFONT02/font00/I<45>"
funcChoiceMessage(mswk20106, mswk20107)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest06stop.lua")
be:DMcase(1)
funcOneMessage(mswk20108)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
