mswk20277 = "TALKFONT02/font01/I<0>"
mswk20278 = "TALKFONT02/font02/I<1>"
mswk20279 = "TALKFONT02/font00/I<2>"
funcChoiceMessage(mswk20277, mswk20278)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02050.lua")
be:DMcase(1)
funcOneMessage(mswk20279)
funcCloseMessage("talk", "n_digilfm", "fW{EX^bt")
be:DMswtEnd()
be:DMrun()
