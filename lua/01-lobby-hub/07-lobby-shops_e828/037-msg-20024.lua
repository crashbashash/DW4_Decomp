mswk20024 = "TALKFONT02/font01/I<6>"
mswk20025 = "TALKFONT02/font02/I<7>"
mswk20026 = "TALKFONT02/font00/I<8>"
funcChoiceMessage(mswk20024, mswk20025)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("weaponshop.lua")
be:DMcase(1)
funcOneMessage(mswk20026)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
