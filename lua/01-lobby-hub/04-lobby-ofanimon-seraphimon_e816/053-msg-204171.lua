mswk204171 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk204171)
mswk20418 = "TALKFONT02/font01/I<238>"
mswk20419 = "TALKFONT02/font02/I<239>"
mswk20420 = "TALKFONT02/font03/I<240>"
mswk20421 = "TALKFONT02/font04/I<241>"
funcChoiceMessage(mswk20418, mswk20419, mswk20420, mswk20421)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02096.lua")
be:DMcase(1)
be:DMsetLua("bML02108.lua")
be:DMcase(2)
be:DMsetLua("bML02109.lua")
be:DMcase(3)
be:DMsetLua("bML02110.lua")
be:DMswtEnd()
be:DMrun()
