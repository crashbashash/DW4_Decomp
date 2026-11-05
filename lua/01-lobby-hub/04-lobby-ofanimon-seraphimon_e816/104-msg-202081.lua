mswk202081 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk202081)
mswk20209 = "TALKFONT02/font01/I<44>"
mswk20210 = "TALKFONT02/font02/I<45>"
mswk20211 = "TALKFONT02/font03/I<46>"
mswk20212 = "TALKFONT02/font04/I<47>"
funcChoiceMessage(mswk20209, mswk20210, mswk20211, mswk20212)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02020.lua")
be:DMcase(1)
be:DMsetLua("bML02021.lua")
be:DMcase(2)
be:DMsetLua("bML02022.lua")
be:DMcase(3)
be:DMsetLua("bML02023.lua")
be:DMswtEnd()
be:DMrun()
