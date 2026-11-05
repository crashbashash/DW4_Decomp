mswk20140 = "TALKFONT02/font01/I<78>"
mswk20141 = "TALKFONT02/font02/I<79>"
funcChoiceMessage(mswk20140, mswk20141)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML01049.lua")
be:DMcase(1)
be:DMsetLua("bML01050.lua")
be:DMswtEnd()
be:DMrun()
