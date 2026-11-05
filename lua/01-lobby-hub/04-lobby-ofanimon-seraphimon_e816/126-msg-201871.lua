mswk201871 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk201871)
mswk20188 = "TALKFONT02/font01/I<0>"
mswk20189 = "TALKFONT02/font02/I<1>"
mswk20190 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20188, mswk20189)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02008.lua")
be:DMcase(1)
funcOneMessage(mswk20190)
funcCloseMessage("talk", "n_digilfm", "Q[gEX^bt")
be:DMswtEnd()
be:DMrun()
