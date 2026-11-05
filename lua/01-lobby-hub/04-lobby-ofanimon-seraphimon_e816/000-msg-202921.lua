mswk202921 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk202921)
mswk20293 = "TALKFONT02/font01/I<126>"
mswk20294 = "TALKFONT02/font02/I<127>"
mswk20295 = "TALKFONT02/font03/I<128>"
mswk20296 = "TALKFONT02/font04/I<129>"
funcChoiceMessage(mswk20293, mswk20294, mswk20295, mswk20296)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02056.lua")
be:DMcase(1)
be:DMsetLua("bML02057.lua")
be:DMcase(2)
be:DMsetLua("bML02058.lua")
be:DMcase(3)
be:DMsetLua("bML02059.lua")
be:DMswtEnd()
be:DMrun()
