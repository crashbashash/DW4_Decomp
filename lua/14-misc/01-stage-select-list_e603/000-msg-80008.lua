mswk80008 = "TALKFONT02/font01/I<0>"
mswk80009 = "TALKFONT02/font02/I<1>"
mswk80010 = "TALKFONT02/font03/I<2>"
mswk80011 = "TALKFONT02/font04/I<3>"
funcChoiceMessage(mswk80008, mswk80009, mswk80010, mswk80011)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("b0001002.lua")
be:DMcase(1)
be:DMsetLua("time00.lua")
be:DMcase(2)
be:DMsetLua("time01.lua")
be:DMcase(3)
be:DMsetLua("time02.lua")
be:DMswtEnd()
be:DMrun()
