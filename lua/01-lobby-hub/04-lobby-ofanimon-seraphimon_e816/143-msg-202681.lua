mswk202681 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk202681)
mswk20269 = "TALKFONT02/font01/I<105>"
mswk20270 = "TALKFONT02/font02/I<106>"
funcChoiceMessage(mswk20269, mswk20270)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02046.lua")
be:DMcase(1)
be:DMsetLua("bML02047.lua")
be:DMswtEnd()
be:DMrun()
