mswk201821 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk201821)
mswk20183 = "TALKFONT02/font01/I<15>"
mswk20184 = "TALKFONT02/font02/I<16>"
funcChoiceMessage(mswk20183, mswk20184)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02009.lua")
be:DMcase(1)
be:DMsetLua("bML02010.lua")
be:DMswtEnd()
be:DMrun()
