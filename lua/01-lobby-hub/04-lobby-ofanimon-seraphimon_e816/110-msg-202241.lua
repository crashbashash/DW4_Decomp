mswk202241 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk202241)
mswk20225 = "TALKFONT02/font01/I<59>"
mswk20226 = "TALKFONT02/font02/I<60>"
funcChoiceMessage(mswk20225, mswk20226)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02027.lua")
be:DMcase(1)
be:DMsetLua("bML02028.lua")
be:DMswtEnd()
be:DMrun()
