local count = 0
local count2 = 0
local count3 = 0
local count4 = 0
local count5 = 0
local count6 = 0
local local_6
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        count6 = count6 + 1
        if be:MDLisLive(be:SYSgetPlayerName(playerIndex), playerIndex) == 1 then
            count = count + 1
        end
        if be:MATgetPlayerMatStat(playerIndex) == 0 then
            count5 = count5 + 1
        elseif be:MATgetPlayerMatStat(playerIndex) == 1 then
            count4 = count4 + 1
        elseif be:MATgetPlayerMatStat(playerIndex) == 2 then
            count2 = count2 + 1
        elseif be:MATgetPlayerMatStat(playerIndex) == 3 then
            count3 = count3 + 1
        end
    end
end
if count2 >= 1 and count3 == 0 then
    if g_IFLG00 ~= 1 then
        be:DMsetSD("MODELCTRL", "g_sbuttonz04", 0, "SQ_OBFGON01")
    else
        be:DMsetSD("MODELCTRL", "g_sbuttonz04", 0, "SQ_FBFGON01")
    end
    be:DMrun()
end
if count4 ~= 0 and count5 == 0 and count3 ~= 0 then
    if g_IFLG00 ~= 1 then
        be:DMsetSD("MODELCTRL", "g_sbuttonz04", 0, "SQ_OBFGON01")
    else
        be:DMsetSD("MODELCTRL", "g_sbuttonz04", 0, "SQ_FBFGON01")
    end
    be:DMrun()
end
if count2 + count3 == count then
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    if g_IFLG00 ~= 1 then
        if count == 1 then
            be:DMchkSD("MODELCTRL", "g_sbuttonz04", 0, "ISSEQNAME", "SQ_OBFGON01", "==0")
        end
        be:DMchkSD("MODELCTRL", "g_sbuttonz04", 0, "ISSEQNAME", "SQ_OBFGON01", "!=0")
        be:DMsetSD("MODELCTRL", "g_sbuttonz04", 0, "SQ_FBFGOF02")
        be:DMsetSD("MODELCTRL", "g_magnetflore1z04", 0, "SQ_SWON1", 15)
        be:DMsetSD("HITLANDMODEL", "hitmagnetflore1z040", 0, "OFFHIT", 45)
        be:DMsetSD("HITLANDMODEL", "hitmagnetflore2z040", 0, "ONHIT", 45)
        be:DMchkSD("MODELCTRL", "g_magnetflore1z04", 0, "ISSEQNAME", "SQ_SWON1", "==0")
        be:DMchkSD("MODELCTRL", "g_magnetflore1z04", 0, "ISSEQNAME", "SQ_SWON1", "!=0")
        g_bluemagnet00 = 0
        g_IFLG00 = 1
        local local_7
        local_7 = g_bluemagnet00 + g_bluemagnet01 + g_bluemagnet02 + g_bluemagnet03 + g_bluemagnet04 + (g_redmagnet00 + g_redmagnet01 + g_redmagnet02 + g_redmagnet03 + g_redmagnet04)
        if local_7 == 3 then
            funcCorrectDemo()
        else
            funcFailDemo()
        end
    elseif count == 1 then
        be:DMchkSD("MODELCTRL", "g_sbuttonz04", 0, "ISSEQNAME", "SQ_FBFGON01", "==0")
    end
    be:DMchkSD("MODELCTRL", "g_sbuttonz04", 0, "ISSEQNAME", "SQ_FBFGON01", "!=0")
    be:DMsetSD("MODELCTRL", "g_sbuttonz04", 0, "SQ_OBFGOF02")
    be:DMsetSD("MODELCTRL", "g_magnetflore1z04", 0, "SQ_SWOF", 15)
    be:DMsetSD("HITLANDMODEL", "hitmagnetflore1z040", 0, "ONHIT", 15)
    be:DMsetSD("HITLANDMODEL", "hitmagnetflore2z040", 0, "OFFHIT", 15)
    be:DMchkSD("MODELCTRL", "g_magnetflore1z04", 0, "ISSEQNAME", "SQ_SWOF", "==0")
    be:DMchkSD("MODELCTRL", "g_magnetflore1z04", 0, "ISSEQNAME", "SQ_SWOF", "!=0")
    g_bluemagnet00 = -1
    g_IFLG00 = 0
    local local_7
    local_7 = g_bluemagnet00 + g_bluemagnet01 + g_bluemagnet02 + g_bluemagnet03 + g_bluemagnet04 + (g_redmagnet00 + g_redmagnet01 + g_redmagnet02 + g_redmagnet03 + g_redmagnet04)
    if local_7 == 3 then
        funcCorrectDemo()
    else
        funcFailDemo()
    end
    be:DMrun()
end
if count2 + count3 == 0 and count6 ~= 1 then
    be:sd("MODELCTRL", nil, -1, "ONCTRL")
    if g_IFLG00 ~= 1 then
        be:DMsetSD("MODELCTRL", "g_sbuttonz04", 0, "SQ_OBFGOF01")
    else
        be:DMsetSD("MODELCTRL", "g_sbuttonz04", 0, "SQ_FBFGOF01")
    end
    be:DMrun()
end
