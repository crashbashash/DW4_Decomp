for local_7 = 0, 3 do
    if be:SYSisJoinPlayer(local_7) == 1 then
        local_5 = local_5 + 1
        if be:MDLisLive(be:SYSgetPlayerName(local_7), local_7) == 1 then
            local_0 = local_0 + 1
        end
        if be:MATgetPlayerMatStat(local_7) == 0 then
            local_4 = local_4 + 1
        elseif be:MATgetPlayerMatStat(local_7) == 1 then
            local_3 = local_3 + 1
        elseif be:MATgetPlayerMatStat(local_7) == 2 then
            local_1 = local_1 + 1
        elseif be:MATgetPlayerMatStat(local_7) == 3 then
            local_2 = local_2 + 1
        end
    end
end
if local_1 >= 1 and local_2 == 0 then
    if g_IFLG09 ~= 1 then
        be:DMsetSD("MODELCTRL", "g_sbuttonz04", 9, "SQ_OLFGON01")
    else
        be:DMsetSD("MODELCTRL", "g_sbuttonz04", 9, "SQ_FLFGON01")
    end
    be:DMrun()
end
if local_3 ~= 0 and local_4 == 0 and local_2 ~= 0 then
    if g_IFLG09 ~= 1 then
        be:DMsetSD("MODELCTRL", "g_sbuttonz04", 9, "SQ_OLFGON01")
    else
        be:DMsetSD("MODELCTRL", "g_sbuttonz04", 9, "SQ_FLFGON01")
    end
    be:DMrun()
end
if local_1 + local_2 == local_0 then
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    if g_IFLG09 ~= 1 then
        if local_0 == 1 then
            be:DMchkSD("MODELCTRL", "g_sbuttonz04", 9, "ISSEQNAME", "SQ_OLFGON01", "==0")
        end
        be:DMchkSD("MODELCTRL", "g_sbuttonz04", 9, "ISSEQNAME", "SQ_OLFGON01", "!=0")
        be:DMsetSD("MODELCTRL", "g_sbuttonz04", 9, "SQ_FLFGOF02")
        be:DMsetSD("MODELCTRL", "g_magnetflore1z04", 9, "SQ_SWON4", 15)
        be:DMsetSD("HITLANDMODEL", "hitmagnetflore1z049", 0, "OFFHIT", 45)
        be:DMsetSD("HITLANDMODEL", "hitmagnetflore2z049", 0, "ONHIT", 45)
        be:DMchkSD("MODELCTRL", "g_magnetflore1z04", 9, "ISSEQNAME", "SQ_SWON4", "==0")
        be:DMchkSD("MODELCTRL", "g_magnetflore1z04", 9, "ISSEQNAME", "SQ_SWON4", "!=0")
        g_redmagnet04 = 0
        g_IFLG09 = 1
        local_7 = g_bluemagnet00 + g_bluemagnet01 + g_bluemagnet02 + g_bluemagnet03 + g_bluemagnet04 + (g_redmagnet00 + g_redmagnet01 + g_redmagnet02 + g_redmagnet03 + g_redmagnet04)
        if local_7 == 3 then
            funcCorrectDemo()
        else
            funcFailDemo()
        end
    elseif local_0 == 1 then
        be:DMchkSD("MODELCTRL", "g_sbuttonz04", 9, "ISSEQNAME", "SQ_FLFGON01", "==0")
    end
    be:DMchkSD("MODELCTRL", "g_sbuttonz04", 9, "ISSEQNAME", "SQ_FLFGON01", "!=0")
    be:DMsetSD("MODELCTRL", "g_sbuttonz04", 9, "SQ_OLFGOF02")
    be:DMsetSD("MODELCTRL", "g_magnetflore1z04", 9, "SQ_SWOF", 15)
    be:DMsetSD("HITLANDMODEL", "hitmagnetflore1z049", 0, "ONHIT", 15)
    be:DMsetSD("HITLANDMODEL", "hitmagnetflore2z049", 0, "OFFHIT", 15)
    be:DMchkSD("MODELCTRL", "g_magnetflore1z04", 9, "ISSEQNAME", "SQ_SWOF", "==0")
    be:DMchkSD("MODELCTRL", "g_magnetflore1z04", 9, "ISSEQNAME", "SQ_SWOF", "!=0")
    g_redmagnet04 = 1
    g_IFLG09 = 0
    local_7 = g_bluemagnet00 + g_bluemagnet01 + g_bluemagnet02 + g_bluemagnet03 + g_bluemagnet04 + (g_redmagnet00 + g_redmagnet01 + g_redmagnet02 + g_redmagnet03 + g_redmagnet04)
    if local_7 == 3 then
        funcCorrectDemo()
    else
        funcFailDemo()
    end
    be:DMrun()
end
if local_1 + local_2 == 0 and local_5 ~= 1 then
    be:sd("MODELCTRL", nil, -1, "ONCTRL")
    if g_IFLG09 ~= 1 then
        be:DMsetSD("MODELCTRL", "g_sbuttonz04", 9, "SQ_OLFGOF01")
    else
        be:DMsetSD("MODELCTRL", "g_sbuttonz04", 9, "SQ_FLFGOF01")
    end
    be:DMrun()
end
