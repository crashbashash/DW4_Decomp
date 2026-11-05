mswk203081 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk203081)
mswk20309 = "TALKFONT02/font01/I<140>"
mswk20310 = "TALKFONT02/font02/I<141>"
mswk20311 = "TALKFONT02/font03/I<142>"
mswk20312 = "TALKFONT02/font04/I<143>"
funcChoiceMessage(mswk20309, mswk20310, mswk20311, mswk20312)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02063.lua")
be:DMcase(1)
be:DMsetLua("bML02064.lua")
be:DMcase(2)
be:DMsetLua("bML02065.lua")
be:DMcase(3)
be:DMsetLua("bML02066.lua")
be:DMswtEnd()
be:DMrun()
