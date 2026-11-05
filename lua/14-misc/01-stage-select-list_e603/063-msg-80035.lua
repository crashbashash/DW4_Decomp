mswk80035 = "TALKFONT02/font02/I<10>"
mswk80048 = "TALKFONT02/font03/I<11>"
mswk80036 = "TALKFONT02/font04/I<12>"
funcChoiceMessage(mswk80049, mswk80035, mswk80048, mswk80036)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("b0001010.lua")
be:DMcase(1)
be:DMsetLua("lv76.lua")
be:DMcase(2)
be:DMsetLua("lv106.lua")
be:DMcase(3)
be:DMsetLua("lv999.lua")
be:DMswtEnd()
be:DMrun()
