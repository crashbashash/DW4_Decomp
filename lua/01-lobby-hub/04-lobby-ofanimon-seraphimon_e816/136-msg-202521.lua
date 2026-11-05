mswk202521 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk202521)
mswk20253 = "TALKFONT02/font01/I<84>"
mswk20254 = "TALKFONT02/font02/I<85>"
mswk20255 = "TALKFONT02/font03/I<86>"
mswk20256 = "TALKFONT02/font04/I<87>"
funcChoiceMessage(mswk20253, mswk20254, mswk20255, mswk20256)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02039.lua")
be:DMcase(1)
be:DMsetLua("bML02040.lua")
be:DMcase(2)
be:DMsetLua("bML02041.lua")
be:DMcase(3)
be:DMsetLua("bML02042.lua")
be:DMswtEnd()
be:DMrun()
