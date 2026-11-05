mswk20015 = "TALKFONT02/font01/I<15>"
mswk20016 = "TALKFONT02/font02/I<16>"
mswk20017 = "TALKFONT02/font00/I<17>"
funcChoiceMessage(mswk20015, mswk20016)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("connoisseur.lua")
be:DMcase(1)
funcOneMessage(mswk20017)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
