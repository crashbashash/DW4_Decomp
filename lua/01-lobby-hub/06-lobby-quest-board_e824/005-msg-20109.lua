mswk20109 = "TALKFONT02/font01/I<46>"
mswk20110 = "TALKFONT02/font02/I<47>"
funcChoiceMessage(mswk20109, mswk20110)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest06end1.lua")
be:DMcase(1)
be:DMsetLua("quest06end2.lua")
be:DMswtEnd()
be:DMrun()
