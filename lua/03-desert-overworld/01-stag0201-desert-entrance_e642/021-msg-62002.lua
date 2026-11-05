for local_2 = 0, 3 do
    if be:SYSisJoinPlayer(local_2) == 1 then
        local_1 = local_1 + be:SYSctlPlayer("HP", "GETHP", local_2, 0)
    end
end
if be:MATisAllPlayer() == 1 and local_1 ~= 0 and be:DMgetCount() == 0 then
    g_messPlayerNo = be:MATgetPlayerNo()
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    funcOpenMessage("mess")
    mswk62002 = "TALKFONT01/font01/I<19>"
    mswk62003 = "TALKFONT01/font02/I<20>"
    funcChoiceMessage(mswk62002, mswk62003)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
    be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
    be:DMsetSD("MATCTRL", nil, -1, "PAUSE")
    be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT")
    be:DMsetSD("MODELCTRL", "g_traingatez02", 0, "SQ_SWON", 20)
    be:DMchkSD("MODELCTRL", "g_traingatez02", 0, "ISSEQNAME", "SQ_SWON", "==0")
    be:DMchkSD("MODELCTRL", "g_traingatez02", 0, "ISSEQNAME", "SQ_SWON", "!=0")
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", 30)
    be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
    be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_STCHANGELP", "==0")
    be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 110)
    be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stag0203", 110)
    be:DMcase(1)
    funcCloseMessage("mess")
    be:DMswtEnd()
    be:DMrun()
end
