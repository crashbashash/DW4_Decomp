mswk204131 = "TALKFONT02/font00/I<216>"
funcOneMessage(mswk204131)
mswk20414 = "TALKFONT02/font01/I<0>"
mswk20415 = "TALKFONT02/font02/I<205>"
mswk20416 = "TALKFONT02/font00/I<235>"
funcChoiceMessage(mswk20414, mswk20415)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02105.lua")
be:DMcase(1)
funcOneMessage(mswk20416)
funcCloseMessage("talk", "n_digilfm", "µñ©UEX^bt")
be:DMswtEnd()
be:DMrun()
