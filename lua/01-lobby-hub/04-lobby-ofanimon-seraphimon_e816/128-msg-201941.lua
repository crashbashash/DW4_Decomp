mswk201941 = "TALKFONT02/font00/I<3>"
funcOneMessage(mswk201941)
mswk20195 = "TALKFONT02/font01/I<26>"
mswk20196 = "TALKFONT02/font02/I<27>"
mswk20197 = "TALKFONT02/font03/I<28>"
funcChoiceMessage(mswk20195, mswk20196, mswk20197)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("bML02014.lua")
be:DMcase(1)
be:DMsetLua("bML02015.lua")
be:DMcase(2)
be:DMsetLua("bML02016.lua")
be:DMswtEnd()
be:DMrun()
