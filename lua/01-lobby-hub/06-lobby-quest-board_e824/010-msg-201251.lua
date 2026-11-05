mswk201251 = "TALKFONT02/font00/I<61>"
funcOneMessage(mswk201251)
mswk20126 = "TALKFONT02/font01/I<62>"
mswk20127 = "TALKFONT02/font02/I<63>"
funcChoiceMessage(mswk20126, mswk20127)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML01043.lua")
be:DMcase(1)
be:DMsetLua("bML01044.lua")
be:DMswtEnd()
be:DMrun()
