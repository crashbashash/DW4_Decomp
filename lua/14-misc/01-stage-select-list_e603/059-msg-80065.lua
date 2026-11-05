mswk80065 = "TALKFONT02/font01/I<25>"
mswk80066 = "TALKFONT02/font02/I<26>"
mswk80083 = "TALKFONT02/font03/I<27>"
funcChoiceMessage(mswk80065, mswk80066, mswk80083)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("sinka14.lua")
be:DMcase(1)
be:DMsetLua("sinka15.lua")
be:DMcase(2)
funcCloseMessage("talk", "n_digilff", "fWt")
be:DMswtEnd()
be:DMrun()
