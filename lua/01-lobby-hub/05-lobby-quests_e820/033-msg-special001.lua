if be:SYSgetPlayerNinzu() == 4 then
    mswkSpecial001 = "TALKFONT02/font00/I<34>"
    funcOneMessage(mswkSpecial001)
    mswkSpecial002 = "TALKFONT02/font00/I<35>"
    funcOneMessage(mswkSpecial002)
    funcCloseMessage("talk", "n_digilff", "fWt")
    be:DMrun()
else
    be:DMsetSD("MODELCTRL", "i_talkwn", 0, "SQ_CLOSEL")
    be:DMsetSD("MODELCTRL", "n_digilffic", 0, "SQ_CLOSEL")
    be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT03/font00/CLR")
    be:DMchkSD("MODELCTRL", "i_talkwn", 0, "ISRUN", "!=0")
    be:DMsetSD("MODELCTRL", "n_digilff", g_npcRamNo, "SQ_WAIT")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", 0)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagIS13", 90)
    be:DMrun()
end
