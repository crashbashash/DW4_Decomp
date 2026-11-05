mswk201421 = "TALKFONT02/font00/I<80>"
funcOneMessage(mswk201421)
mswk201422 = "TALKFONT02/font00/I<81>"
funcOneMessage(mswk201422)
mswk201423 = "TALKFONT02/font00/I<82>"
funcOneMessage(mswk201423)
mswk20143 = "TALKFONT02/font01/I<83>"
mswk20144 = "TALKFONT02/font02/I<84>"
mswk20145 = "TALKFONT02/font00/I<85>"
funcChoiceMessage(mswk20143, mswk20144)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest08.lua")
be:DMcase(1)
funcOneMessage(mswk20145)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
