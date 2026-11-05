mswk203241 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk203241)
mswk20325 = "TALKFONT02/font01/I<158>"
mswk20326 = "TALKFONT02/font02/I<159>"
mswk20327 = "TALKFONT02/font03/I<160>"
funcChoiceMessage(mswk20325, mswk20326, mswk20327)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02070.lua")
be:DMcase(1)
be:DMsetLua("bML02071.lua")
be:DMcase(2)
be:DMsetLua("bML02072.lua")
be:DMswtEnd()
be:DMrun()
