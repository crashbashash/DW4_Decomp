mswk20084 = "TALKFONT02/font01/I<28>"
mswk20085 = "TALKFONT02/font02/I<29>"
funcChoiceMessage(mswk20084, mswk20085)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML01029.lua")
be:DMcase(1)
be:DMsetLua("bML01029.lua")
be:DMswtEnd()
be:DMrun()
