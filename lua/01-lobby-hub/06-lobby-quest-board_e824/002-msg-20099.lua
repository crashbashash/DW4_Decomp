mswk20099 = "TALKFONT02/font01/I<25>"
mswk20100 = "TALKFONT02/font02/I<26>"
mswk20101 = "TALKFONT02/font00/I<40>"
funcChoiceMessage(mswk20099, mswk20100)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest06stop.lua")
be:DMcase(1)
funcOneMessage(mswk20101)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
