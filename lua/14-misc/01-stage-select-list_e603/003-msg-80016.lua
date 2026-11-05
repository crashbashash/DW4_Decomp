mswk80016 = "TALKFONT02/font01/I<7>"
mswk80017 = "TALKFONT02/font02/I<8>"
mswk80027 = "TALKFONT02/font03/I<9>"
funcChoiceMessage(mswk80016, mswk80017, mswk80027)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
funcCloseMessage("talk", "n_digilff", "fWt")
be:DMcase(1)
be:DMsetLua("time06.lua")
be:DMcase(2)
be:DMsetLua("fieldquest.lua")
be:DMswtEnd()
be:DMrun()
