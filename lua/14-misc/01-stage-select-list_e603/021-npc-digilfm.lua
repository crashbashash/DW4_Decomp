funcOpenMessage("talk", "n_digilfm", "fWt")
mswk80032 = "TALKFONT02/font00/I<55>"
funcOneMessage(mswk80032)
mswk80049 = "TALKFONT02/font01/I<0>"
mswk80033 = "TALKFONT02/font02/I<56>"
mswk80047 = "TALKFONT02/font03/I<57>"
mswk80034 = "TALKFONT02/font04/I<58>"
mswk80037 = "TALKFONT02/font00/I<59>"
funcChoiceMessage(mswk80049, mswk80033, mswk80047, mswk80034)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("b0001004.lua")
be:DMcase(1)
be:DMsetLua("lv16.lua")
be:DMcase(2)
be:DMsetLua("lv36.lua")
be:DMcase(3)
be:DMsetLua("lv46.lua")
be:DMswtEnd()
be:DMrun()
