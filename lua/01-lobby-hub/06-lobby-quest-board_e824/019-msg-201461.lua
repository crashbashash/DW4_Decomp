mswk201461 = "TALKFONT02/font00/I<86>"
funcOneMessage(mswk201461)
mswk201462 = "TALKFONT02/font00/I<87>"
funcOneMessage(mswk201462)
mswk201463 = "TALKFONT02/font00/I<88>"
funcOneMessage(mswk201463)
mswk201464 = "TALKFONT02/font00/I<89>"
funcOneMessage(mswk201464)
mswk201465 = "TALKFONT02/font00/I<90>"
funcOneMessage(mswk201465)
mswk201466 = "TALKFONT02/font00/I<82>"
funcOneMessage(mswk201466)
mswk20147 = "TALKFONT02/font01/I<83>"
mswk20148 = "TALKFONT02/font02/I<84>"
mswk20149 = "TALKFONT02/font00/I<85>"
funcChoiceMessage(mswk20147, mswk20148)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest08.lua")
be:DMcase(1)
funcOneMessage(mswk20149)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
