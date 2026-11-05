g_StChangeKind = "trans"
if be:MATisAllPlayer() == 1 and be:DMgetCount() == 0 then
    be:sd("MODELCTRL", "i_timenm0", 0, "SQ_STOP")
    mswk70027 = "STCHGFONT00/font00/I<10>"
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    if local_1 ~= 0 then
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BHLFOUT30")
        be:DMsetSD("MODELCTRL", "i_zzstchgwb", local_0, "GENERATE", "SQ_STOPEN", 10)
        be:DMsetSD("SELECTCTRL", "i_zzstchgwn", local_0, "GENERATE", "V<0,-16,0>/V<0,0,0>", 10)
        be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "STCHGFONT00/font00/CENTER")
        if local_0 == 0 then
            be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<0.9,0.47,0.47>")
        elseif local_0 == 1 then
            be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<0.47,0.47,0.9>")
        elseif local_0 == 2 then
            be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<0.9,0.9,0.47>")
        elseif local_0 == 3 then
            be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<0.47,0.9,0.47>")
        end
        be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk70027, 10)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "STCHGFONT00/font00/SET", 30)
        be:DMchkSD("MODELCTRL", "i_zzstchgwb", local_0, "ISRUN", "==0")
        be:DMchkSD("SELECTCTRL", "i_zzstchgwn", local_0, "ISEND", "!=0")
        be:DMchkSD("SELECTCTRL", "i_zzstchgwn", local_0, "ISSELECTNOW", "==1")
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "STCHGFONT00/font00/CLR")
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
        be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT")
        for local_6 = 0, 3 do
            if be:SYSisJoinPlayer(local_6) == 1 then
                be:DMsetSD("PLAYER", be:SYSgetPlayerName(local_6), local_6, "SQ_EXIT", local_5)
                local_5 = local_5 + 20
            end
        end
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", local_5 + 40)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_STCHANGELP", "==0")
        be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<0>", 10)
        be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stagML11", 10)
        be:DMcase(1)
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
        be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 30)
        if be:FLGisOn(144) ~= 1 then
            be:DMsetSD("MODELCTRL", "i_timenm0", 0, "SQ_RESTART", 30)
        end
        be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "ENABLE", 30)
        be:DMcase(-1)
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
        be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 30)
        if be:FLGisOn(144) ~= 1 then
            be:DMsetSD("MODELCTRL", "i_timenm0", 0, "SQ_RESTART", 30)
        end
        be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "ENABLE", 30)
        be:DMswtEnd()
        be:DMrun()
    else
        be:sd("PLAYER", nil, -1, "ONCTRL")
        be:sd("ENEMY", nil, -1, "ONCTRL")
    end
end
