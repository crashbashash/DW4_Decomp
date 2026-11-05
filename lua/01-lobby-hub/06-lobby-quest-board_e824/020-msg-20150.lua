mswk20150 = "TALKFONT02/font01/I<91>"
mswk20151 = "TALKFONT02/font02/I<92>"
mswk20152 = "TALKFONT02/font00/I<93>"
funcChoiceMessage(mswk20150, mswk20151)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("quest08.lua")
be:DMcase(1)
funcOneMessage(mswk20152)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
