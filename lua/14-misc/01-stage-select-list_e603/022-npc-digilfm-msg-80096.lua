funcOpenMessage("talk", "n_digilfm", "fWt")
mswk80096 = "TALKFONT02/font00/I<77>"
funcOneMessage(mswk80096)
mswk80097 = "TALKFONT02/font01/I<78>"
mswk80098 = "TALKFONT02/font02/I<79>"
mswk80099 = "TALKFONT02/font03/I<80>"
funcChoiceMessage(mswk80097, mswk80098, mswk80099)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMcase(1)
be:DMsetLua("hard.lua")
be:DMcase(2)
be:DMsetLua("veryhard.lua")
be:DMswtEnd()
be:DMrun()
