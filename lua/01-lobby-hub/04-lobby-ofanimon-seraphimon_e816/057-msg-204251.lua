mswk204251 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk204251)
mswk20426 = "TALKFONT02/font01/I<249>"
mswk20427 = "TALKFONT02/font02/I<250>"
mswk20428 = "TALKFONT02/font03/I<241>"
funcChoiceMessage(mswk20426, mswk20427, mswk20428)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02099.lua")
be:DMcase(1)
be:DMsetLua("bML02112.lua")
be:DMcase(2)
be:DMsetLua("bML02113.lua")
be:DMswtEnd()
be:DMrun()
