funcOpenMessage("talk", "n_digilfm", "fWt")
mswk80204 = "TALKFONT02/font00/I<81>"
funcOneMessage(mswk80204)
mswk80205 = "TALKFONT02/font01/I<82>"
mswk80206 = "TALKFONT02/font02/I<83>"
funcChoiceMessage(mswk80205, mswk80206)
be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
be:DMcase(0)
funcCloseMessage("talk", "n_digilfm", "fWt", 1, "demo")
be:DMsetSD("MODELCTRL", "i_stback", 0, "GENERATE", "SQ_OPEN")
be:DMchkSD("MODELCTRL", "i_stback", 0, "ISRUN", "==0")
be:DMsetLua("stchg01.lua")
be:DMcase(1)
funcCloseMessage("talk", "n_digilfm", "fWt")
be:DMswtEnd()
be:DMrun()
