mswk200931 = "TALKFONT02/font00/I<32>"
funcOneMessage(mswk200931)
mswk200932 = "TALKFONT02/font00/I<33>"
funcOneMessage(mswk200932)
mswk200933 = "TALKFONT02/font00/I<34>"
funcOneMessage(mswk200933)
mswk20094 = "TALKFONT02/font01/I<35>"
mswk20095 = "TALKFONT02/font02/I<36>"
funcChoiceMessage(mswk20094, mswk20095)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest05end1.lua")
be:DMcase(1)
be:DMsetLua("quest05end2.lua")
be:DMswtEnd()
be:DMrun()
