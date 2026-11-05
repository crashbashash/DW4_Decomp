mswk200771 = "TALKFONT02/font00/I<21>"
funcOneMessage(mswk200771)
mswk200772 = "TALKFONT02/font00/I<22>"
funcOneMessage(mswk200772)
mswk20078 = "TALKFONT02/font01/I<23>"
mswk20079 = "TALKFONT02/font02/I<24>"
mswk20080 = "TALKFONT02/font00/I<20>"
funcChoiceMessage(mswk20078, mswk20079)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest05.lua")
be:DMcase(1)
funcOneMessage(mswk20080)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
