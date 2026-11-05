g_StChangeKind = "stay"
if be:MATisAllPlayer() == 1 and be:DMgetCount() == 0 then
    if be:FLGisOn(121) == 0 then
        funcStageChange("dngq3b2e", 0)
    else
        be:sd("MODELCTRL", "i_timenm0", 0, "SQ_STOP")
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:sd("ENEMY", nil, -1, "OFCTRL")
        if local_1 ~= 0 then
            be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BHLFOUT30")
            be:DMsetSD("MODELCTRL", "i_zzstchgwb", local_0, "GENERATE", "SQ_OPEN", 10)
            be:DMsetSD("SELECTCTRL", "i_zzstchgwn", local_0, "GENERATE", 10)
            be:DMchkSD("MODELCTRL", "i_zzstchgwb", local_0, "ISRUN", "==0")
            be:DMchkSD("SELECTCTRL", "i_zzstchgwn", local_0, "ISEND", "!=0")
            be:DMchkSD("SELECTCTRL", "i_zzstchgwn", local_0, "ISSELECTNOW", "==1")
            be:DMsetSD("MODELCTRL", "i_zzstchgwb", local_0, "SQ_CLOSE")
            be:DMchkSD("SELECTCTRL", "i_zzstchgwn", local_0, "ISEND", "==0")
            be:DMswtSD("SELECTCTRL", "i_zzstchgwn", local_0, "GETSELECT")
            be:DMcase(0)
            be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "DISABLE")
            be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BHLFIN30", "==0")
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BHLFIN30", "!=0")
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "!=0")
            for local_4 = 0, 3 do
                if be:SYSisJoinPlayer(local_4) == 1 then
                    if local_7 == 0 then
                        be:DMchkSD("MODELCTRL", be:SYSgetPlayerName(local_4), local_4, "ISRUN", "!=0")
                    end
                end
            end
            be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01")
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_STCHANGELP", "==0")
            be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 10)
            be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "dngq3b2e", 10)
            be:DMcase(1)
            be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
            be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 30)
            be:DMsetSD("MODELCTRL", "i_timenm0", 0, "SQ_RESTART", 30)
            be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "ENABLE", 30)
            be:DMcase(-1)
            be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
            be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 30)
            be:DMsetSD("MODELCTRL", "i_timenm0", 0, "SQ_RESTART", 30)
            be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "ENABLE", 30)
            be:DMswtEnd()
            be:DMrun()
        else
            be:sd("PLAYER", nil, -1, "ONCTRL")
            be:sd("ENEMY", nil, -1, "ONCTRL")
        end
    end
end
