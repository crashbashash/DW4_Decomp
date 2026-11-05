mswk202731 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk202731)
mswk20274 = "TALKFONT02/font01/I<0>"
mswk20275 = "TALKFONT02/font02/I<1>"
mswk20276 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20274, mswk20275)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02045.lua")
be:DMcase(1)
funcOneMessage(mswk20276)
funcCloseMessage("talk", "n_digilff", "÷wf[^eCRE¿X^bt")
be:DMswtEnd()
be:DMrun()
