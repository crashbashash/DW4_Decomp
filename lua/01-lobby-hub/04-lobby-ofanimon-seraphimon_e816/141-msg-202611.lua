mswk202611 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk202611)
mswk20262 = "TALKFONT02/font01/I<0>"
mswk20263 = "TALKFONT02/font02/I<1>"
mswk20264 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20262, mswk20263)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02038.lua")
be:DMcase(1)
funcOneMessage(mswk20264)
funcCloseMessage("talk", "n_digilff", "«Ùñp[^EX^bt")
be:DMswtEnd()
be:DMrun()
