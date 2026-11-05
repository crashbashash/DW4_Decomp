mswk201211 = "TALKFONT02/font00/I<57>"
funcOneMessage(mswk201211)
mswk201212 = "TALKFONT02/font00/I<58>"
funcOneMessage(mswk201212)
mswk20122 = "TALKFONT02/font01/I<59>"
mswk20123 = "TALKFONT02/font02/I<60>"
mswk20124 = "TALKFONT02/font00/I<56>"
funcChoiceMessage(mswk20122, mswk20123)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML01042.lua")
be:DMcase(1)
funcOneMessage(mswk20124)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
