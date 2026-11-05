if be:FLGisOn(121) == 1 then
    if be:MATisAllPlayer() == 1 and be:DMgetCount() <= 0 then
        if be:DMgetCount() == -1 then
            be:sd("SUBWND", nil, -1, "REMOVE")
            be:DMchkSD("SUBWND", nil, -1, "ISRUN", "!=0")
        end
        g_messPlayerNo = be:MATgetPlayerNo()
        if local_0 ~= 0 then
            be:FLGset(386, 1)
            be:sd("MODELCTRL", "i_timenm0", 0, "SQ_STOP")
            be:sd("PLAYER", nil, -1, "OFCTRL")
            be:sd("ENEMY", nil, -1, "OFCTRL")
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
            be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE02")
            be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN", 60)
            be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "TALKFONT01/font00/CENTER", 60)
            g_talk = "mess"
            g_page = 0
            g_messPlayerNo = 0
            be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
            be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "==0")
            be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
            funcOneMessage(mswk61062)
            funcOneMessage(mswk61063)
            funcOneMessage(mswk61064)
            be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
            be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
            be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "QS_HURRY/F<1.0>/F<0.0>/F<60>")
            be:DMsetSD("SOUND", nil, -1, "BGMSTOP", 61)
            be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWALK", 30)
            be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT", 90)
            be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 90)
            be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML11", 90)
            be:DMrun()
        end
    else
    end
end
be:MATsetRun(0)
