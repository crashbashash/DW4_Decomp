mswk20032 = "TALKFONT02/font01/I<15>"
mswk20033 = "TALKFONT02/font02/I<16>"
mswk200331 = "TALKFONT02/font00/I<17>"
funcChoiceMessage(mswk20032, mswk20033)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("junkshop.lua")
be:DMcase(1)
funcOneMessage(mswk200331)
funcCloseMessage("talk", "n_metete", "^Ge")
be:DMswtEnd()
be:DMrun()
