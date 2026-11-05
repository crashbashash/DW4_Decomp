mswk204051 = "TALKFONT02/font00/I<216>"
funcOneMessage(mswk204051)
mswk20406 = "TALKFONT02/font01/I<0>"
mswk20407 = "TALKFONT02/font02/I<205>"
mswk20408 = "TALKFONT02/font00/I<230>"
funcChoiceMessage(mswk20406, mswk20407)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02102.lua")
be:DMcase(1)
funcOneMessage(mswk20408)
funcCloseMessage("talk", "n_digilff", "AreBE`bvEX^bt")
be:DMswtEnd()
be:DMrun()
