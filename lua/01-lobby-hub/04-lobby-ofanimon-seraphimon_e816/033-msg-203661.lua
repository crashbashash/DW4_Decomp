mswk203661 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk203661)
mswk20367 = "TALKFONT02/font01/I<196>"
mswk20368 = "TALKFONT02/font02/I<197>"
mswk20369 = "TALKFONT02/font03/I<198>"
funcChoiceMessage(mswk20367, mswk20368, mswk20369)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02088.lua")
be:DMcase(1)
be:DMsetLua("bML02089.lua")
be:DMcase(2)
be:DMsetLua("bML02090.lua")
be:DMswtEnd()
be:DMrun()
