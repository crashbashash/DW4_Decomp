mswk80056 = "TALKFONT02/font02/I<16>"
mswk80057 = "TALKFONT02/font03/I<17>"
mswk80058 = "TALKFONT02/font04/I<18>"
funcChoiceMessage(mswk80029, mswk80056, mswk80057, mswk80058)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("b0001007.lua")
be:DMcase(1)
be:DMsetLua("sinka05.lua")
be:DMcase(2)
be:DMsetLua("sinka06.lua")
be:DMcase(3)
be:DMsetLua("sinka07.lua")
be:DMswtEnd()
be:DMrun()
