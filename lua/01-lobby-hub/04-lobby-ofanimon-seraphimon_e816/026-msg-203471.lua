mswk203471 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk203471)
mswk20348 = "TALKFONT02/font01/I<0>"
mswk20349 = "TALKFONT02/font02/I<1>"
mswk20350 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20348, mswk20349)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02075.lua")
be:DMcase(1)
funcOneMessage(mswk20350)
funcCloseMessage("talk", "n_digilfm", "XLVXeEX^bt")
be:DMswtEnd()
be:DMrun()
