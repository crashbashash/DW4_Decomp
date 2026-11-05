mswk80053 = "TALKFONT02/font02/I<13>"
mswk80054 = "TALKFONT02/font03/I<14>"
mswk80055 = "TALKFONT02/font04/I<15>"
funcChoiceMessage(mswk80029, mswk80053, mswk80054, mswk80055)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("b0001006.lua")
be:DMcase(1)
be:DMsetLua("sinka02.lua")
be:DMcase(2)
be:DMsetLua("sinka03.lua")
be:DMcase(3)
be:DMsetLua("sinka04.lua")
be:DMswtEnd()
be:DMrun()
