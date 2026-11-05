funcOpenMessage("talk", "n_digilff", "fWt")
mswk80028 = "TALKFONT02/font00/I<51>"
funcOneMessage(mswk80028)
mswk80029 = "TALKFONT02/font01/I<0>"
mswk80030 = "TALKFONT02/font02/I<52>"
mswk80051 = "TALKFONT02/font03/I<53>"
mswk80052 = "TALKFONT02/font04/I<54>"
funcChoiceMessage(mswk80029, mswk80030, mswk80051, mswk80052)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("b0001005.lua")
be:DMcase(1)
be:DMsetLua("sinka.lua")
be:DMcase(2)
be:DMsetLua("sinka00.lua")
be:DMcase(3)
be:DMsetLua("sinka01.lua")
be:DMswtEnd()
be:DMrun()
