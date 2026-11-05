mswk80059 = "TALKFONT02/font02/I<19>"
mswk80060 = "TALKFONT02/font03/I<20>"
mswk80061 = "TALKFONT02/font04/I<21>"
funcChoiceMessage(mswk80029, mswk80059, mswk80060, mswk80061)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("b0001008.lua")
be:DMcase(1)
be:DMsetLua("sinka08.lua")
be:DMcase(2)
be:DMsetLua("sinka09.lua")
be:DMcase(3)
be:DMsetLua("sinka10.lua")
be:DMswtEnd()
be:DMrun()
