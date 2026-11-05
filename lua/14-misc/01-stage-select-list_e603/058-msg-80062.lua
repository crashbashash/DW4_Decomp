mswk80062 = "TALKFONT02/font02/I<22>"
mswk80063 = "TALKFONT02/font03/I<23>"
mswk80064 = "TALKFONT02/font04/I<24>"
funcChoiceMessage(mswk80029, mswk80062, mswk80063, mswk80064)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("b0001009.lua")
be:DMcase(1)
be:DMsetLua("sinka11.lua")
be:DMcase(2)
be:DMsetLua("sinka12.lua")
be:DMcase(3)
be:DMsetLua("sinka13.lua")
be:DMswtEnd()
be:DMrun()
