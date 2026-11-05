mswk20051 = "TALKFONT02/font01/I<17>"
mswk20052 = "TALKFONT02/font02/I<11>"
mswk20053 = "TALKFONT02/font00/I<18>"
funcChoiceMessage(mswk20051, mswk20052)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest02stop.lua")
be:DMcase(1)
funcOneMessage(mswk20053)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
