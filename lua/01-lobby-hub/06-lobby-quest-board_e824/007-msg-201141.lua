mswk201141 = "TALKFONT02/font00/I<51>"
funcOneMessage(mswk201141)
mswk20115 = "TALKFONT02/font01/I<52>"
mswk20116 = "TALKFONT02/font02/I<42>"
mswk20117 = "TALKFONT02/font00/I<53>"
funcChoiceMessage(mswk20115, mswk20116)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest06stop.lua")
be:DMcase(1)
funcOneMessage(mswk20117)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
