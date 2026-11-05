mswk201681 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk201681)
mswk20169 = "TALKFONT02/font01/I<4>"
mswk20170 = "TALKFONT02/font02/I<5>"
mswk20171 = "TALKFONT02/font03/I<6>"
funcChoiceMessage(mswk20169, mswk20170, mswk20171)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02003.lua")
be:DMcase(1)
be:DMsetLua("bML02004.lua")
be:DMcase(2)
be:DMsetLua("bML02005.lua")
be:DMswtEnd()
be:DMrun()
