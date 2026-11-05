mswk20249 = "TALKFONT02/font01/I<0>"
mswk20250 = "TALKFONT02/font02/I<1>"
mswk20251 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20249, mswk20250)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02038.lua")
be:DMcase(1)
funcOneMessage(mswk20251)
funcCloseMessage("talk", "n_digilff", "«Ùñp[^EX^bt")
be:DMswtEnd()
be:DMrun()
