mswk202801 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk202801)
mswk20281 = "TALKFONT02/font01/I<113>"
mswk20282 = "TALKFONT02/font02/I<114>"
funcChoiceMessage(mswk20281, mswk20282)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02051.lua")
be:DMcase(1)
be:DMsetLua("bML02052.lua")
be:DMswtEnd()
be:DMrun()
