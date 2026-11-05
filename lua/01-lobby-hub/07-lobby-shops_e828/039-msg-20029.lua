mswk20029 = "TALKFONT02/font01/I<12>"
mswk20030 = "TALKFONT02/font02/I<13>"
mswk20031 = "TALKFONT02/font00/I<14>"
funcChoiceMessage(mswk20029, mswk20030)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("chipshop.lua")
be:DMcase(1)
funcOneMessage(mswk20031)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
