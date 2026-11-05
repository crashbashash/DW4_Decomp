mswk20205 = "TALKFONT02/font01/I<0>"
mswk20206 = "TALKFONT02/font02/I<1>"
mswk20207 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20205, mswk20206)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02019.lua")
be:DMcase(1)
funcOneMessage(mswk20207)
funcCloseMessage("talk", "n_digilfm", "tH_EX^bt")
be:DMswtEnd()
be:DMrun()
