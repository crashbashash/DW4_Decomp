mswk201331 = "TALKFONT02/font00/I<72>"
funcOneMessage(mswk201331)
mswk20134 = "TALKFONT02/font01/I<73>"
mswk20135 = "TALKFONT02/font02/I<74>"
mswk20136 = "TALKFONT02/font00/I<75>"
funcChoiceMessage(mswk20134, mswk20135)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest07stop1.lua")
be:DMcase(1)
funcOneMessage(mswk20136)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
