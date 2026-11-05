mswk203541 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk203541)
mswk20355 = "TALKFONT02/font01/I<189>"
mswk20356 = "TALKFONT02/font02/I<190>"
funcChoiceMessage(mswk20355, mswk20356)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02083.lua")
be:DMcase(1)
be:DMsetLua("bML02084.lua")
be:DMswtEnd()
be:DMrun()
