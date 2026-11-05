mswk202171 = "TALKFONT02/font00/I<25>"
funcOneMessage(mswk202171)
mswk20218 = "TALKFONT02/font01/I<0>"
mswk20219 = "TALKFONT02/font02/I<1>"
mswk20220 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20218, mswk20219)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02019.lua")
be:DMcase(1)
funcOneMessage(mswk20220)
funcCloseMessage("talk", "n_digilfm", "tH_EX^bt")
be:DMswtEnd()
be:DMrun()
