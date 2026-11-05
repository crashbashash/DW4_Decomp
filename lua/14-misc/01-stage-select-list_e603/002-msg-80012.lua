mswk80012 = "TALKFONT02/font01/I<0>"
mswk80013 = "TALKFONT02/font02/I<4>"
mswk80014 = "TALKFONT02/font03/I<5>"
mswk80015 = "TALKFONT02/font04/I<6>"
funcChoiceMessage(mswk80012, mswk80013, mswk80014, mswk80015)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("b0001003.lua")
be:DMcase(1)
be:DMsetLua("time03.lua")
be:DMcase(2)
be:DMsetLua("time04.lua")
be:DMcase(3)
be:DMsetLua("time05.lua")
be:DMswtEnd()
be:DMrun()
