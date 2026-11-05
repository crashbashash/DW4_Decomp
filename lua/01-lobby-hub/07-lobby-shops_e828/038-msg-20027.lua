mswk20027 = "TALKFONT02/font01/I<9>"
mswk20028 = "TALKFONT02/font02/I<10>"
mswk200281 = "TALKFONT02/font00/I<11>"
funcChoiceMessage(mswk20027, mswk20028)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("armorshop.lua")
be:DMcase(1)
funcOneMessage(mswk200281)
funcCloseMessage("talk", "n_digilff", "fWt")
be:DMswtEnd()
be:DMrun()
