mswk203381 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk203381)
mswk20339 = "TALKFONT02/font01/I<168>"
mswk20340 = "TALKFONT02/font02/I<169>"
mswk20341 = "TALKFONT02/font03/I<170>"
mswk20342 = "TALKFONT02/font04/I<171>"
funcChoiceMessage(mswk20339, mswk20340, mswk20341, mswk20342)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02076.lua")
be:DMcase(1)
be:DMsetLua("bML02077.lua")
be:DMcase(2)
be:DMsetLua("bML02078.lua")
be:DMcase(3)
be:DMsetLua("bML02079.lua")
be:DMswtEnd()
be:DMrun()
