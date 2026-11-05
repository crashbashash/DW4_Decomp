mswk20162 = "TALKFONT02/font01/I<99>"
mswk20163 = "TALKFONT02/font02/I<100>"
mswk20164 = "TALKFONT02/font00/I<101>"
funcChoiceMessage(mswk20162, mswk20163)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
be:DMsetLua("keychain.lua")
be:DMcase(1)
funcOneMessage(mswk20164)
funcCloseMessage("talk", "n_prmame", "vX}")
be:DMswtEnd()
be:DMrun()
