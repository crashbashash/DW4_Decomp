mswk200571 = "TALKFONT02/font00/I<21>"
funcOneMessage(mswk200571)
mswk200572 = "TALKFONT02/font00/I<22>"
funcOneMessage(mswk200572)
mswk20058 = "TALKFONT02/font01/I<8>"
mswk20059 = "TALKFONT02/font02/I<9>"
mswk20060 = "TALKFONT02/font00/I<20>"
funcChoiceMessage(mswk20058, mswk20059)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest03.lua")
be:DMcase(1)
funcOneMessage(mswk20060)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
