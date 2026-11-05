mswk20081 = "TALKFONT02/font01/I<25>"
mswk20082 = "TALKFONT02/font02/I<26>"
mswk20083 = "TALKFONT02/font00/I<27>"
funcChoiceMessage(mswk20081, mswk20082)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest05stop.lua")
be:DMcase(1)
funcOneMessage(mswk20083)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
