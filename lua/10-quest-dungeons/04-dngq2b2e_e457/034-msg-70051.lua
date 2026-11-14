g_StChangeKind = "trans"
if be:MATisAllPlayer() == 1 and be:DMgetCount() == 0 then
    be:sd("MODELCTRL", "i_timenm0", 0, "SQ_STOP")
    mswk70051 = "STCHGFONT00/font00/I<10>"
    local playerNo = be:MATgetPlayerNo()
    local hp = be:SYSctlPlayer("HP", "GETHP", playerNo, 0)
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    if hp ~= 0 then
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BHLFOUT30")
        be:DMsetSD("MODELCTRL", "i_zzstchgwb", playerNo, "GENERATE", "SQ_STOPEN", 10)
        be:DMsetSD("SELECTCTRL", "i_zzstchgwn", playerNo, "GENERATE", "V<0,-16,0>/V<0,0,0>", 10)
        be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "STCHGFONT00/font00/CENTER")
        if playerNo == 0 then
            be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<0.9,0.47,0.47>")
        elseif playerNo == 1 then
            be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<0.47,0.47,0.9>")
        elseif playerNo == 2 then
            be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<0.9,0.9,0.47>")
        elseif playerNo == 3 then
            be:DMsetSD("TEXTCTL", nil, -1, "COLOR", "STCHGFONT00/font00/V<0.47,0.9,0.47>")
        end
        be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk70051, 10)
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "STCHGFONT00/font00/SET", 30)
        be:DMchkSD("MODELCTRL", "i_zzstchgwb", playerNo, "ISRUN", "==0")
        be:DMchkSD("SELECTCTRL", "i_zzstchgwn", playerNo, "ISEND", "!=0")
        be:DMchkSD("SELECTCTRL", "i_zzstchgwn", playerNo, "ISSELECTNOW", "==1")
        be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "STCHGFONT00/font00/CLR")
        be:DMsetSD("MODELCTRL", "i_zzstchgwb", playerNo, "SQ_CLOSE")
        be:DMchkSD("SELECTCTRL", "i_zzstchgwn", playerNo, "ISEND", "==0")
        be:DMswtSD("SELECTCTRL", "i_zzstchgwn", playerNo, "GETSELECT")
        be:DMcase(0)
        be:DMsetSD("STAGECTL", nil, -1, "PADINPUT", "DISABLE")
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BHLFIN30", "==0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BHLFIN30", "!=0")
        be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "!=0")
        local local_2
        local local_3
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                local hp2 = be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
                if hp2 == 0 then
                    be:DMchkSD("MODELCTRL", be:SYSgetPlayerName(playerIndex), playerIndex, "ISRUN", "!=0")
                end
            end
        end
        local local_4
        local offset = 0
        be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT")
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                be:DMsetSD("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SQ_EXIT", offset)
                offset = offset + 20
            end
        end
        be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_STCHANGE01", offset + 40)
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
