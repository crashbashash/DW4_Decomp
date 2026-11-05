mswk202361 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk202361)
mswk20237 = "TALKFONT02/font01/I<65>"
mswk20238 = "TALKFONT02/font02/I<66>"
mswk20239 = "TALKFONT02/font03/I<67>"
mswk20240 = "TALKFONT02/font04/I<68>"
funcChoiceMessage(mswk20237, mswk20238, mswk20239, mswk20240)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02032.lua")
be:DMcase(1)
be:DMsetLua("bML02033.lua")
be:DMcase(2)
be:DMsetLua("bML02034.lua")
be:DMcase(3)
be:DMsetLua("bML02035.lua")
be:DMswtEnd()
be:DMrun()
