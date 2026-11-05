mswk80103 = "TALKFONT02/font01/I<28>"
mswk80104 = "TALKFONT02/font02/I<29>"
mswk80105 = "TALKFONT02/font03/I<30>"
mswk80050 = "TALKFONT02/font04/I<31>"
funcChoiceMessage(mswk80103, mswk80104, mswk80105, mswk80050)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("lv50.lua")
be:DMcase(1)
be:DMsetLua("lv100.lua")
be:DMcase(2)
be:DMsetLua("lv200.lua")
be:DMcase(3)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
