if not g_HP0 then
    g_HP0 = 0
end
if not g_HP1 then
    g_HP1 = 0
end
if not g_HP2 then
    g_HP2 = 0
end
if not g_HP3 then
    g_HP3 = 0
end
if not g_HP4 then
    g_HP4 = 0
end
if not g_HP5 then
    g_HP5 = 0
end
if not g_HP6 then
    g_HP6 = 0
end
if not g_HP7 then
    g_HP7 = 0
end
if not g_shield0 then
    g_shield0 = 0
end
if not g_shield1 then
    g_shield1 = 0
end
if not g_shield2 then
    g_shield2 = 0
end
if not g_shield3 then
    g_shield3 = 0
end
if not g_shield4 then
    g_shield4 = 0
end
if not g_shield5 then
    g_shield5 = 0
end
if not g_shield6 then
    g_shield6 = 0
end
if not g_shield7 then
    g_shield7 = 0
end
local ramNo = be:MDLgetRamNo()
if be:MDLisCallName("chack") == 1 then
    if be:MDLisLive("x_028eblst01a", 0) == 1 and be:MDLisLive("x_028eblst01a", 1) == 1 and be:MDLisLive("x_028eblst01a", 2) == 1 then
        be:sd("MODELCTRL", "e_rare", ramNo, "SQ_WAIT", 0)
    else
        be:sd("MODELCTRL", "e_rare", ramNo, "SQ_FIRE1", 0)
    end
elseif be:MDLisCallName("live") == 1 then
    if ramNo == 0 then
        g_HP0 = be:MDLgetHp()
        g_shield0 = 1
    elseif ramNo == 1 then
        g_HP1 = be:MDLgetHp()
        g_shield1 = 1
    elseif ramNo == 2 then
        g_HP2 = be:MDLgetHp()
        g_shield2 = 1
    elseif ramNo == 3 then
        g_HP3 = be:MDLgetHp()
        g_shield3 = 1
    elseif ramNo == 4 then
        g_HP4 = be:MDLgetHp()
        g_shield4 = 1
    elseif ramNo == 5 then
        g_HP5 = be:MDLgetHp()
        g_shield5 = 1
    elseif ramNo == 6 then
        g_HP6 = be:MDLgetHp()
        g_shield6 = 1
    elseif ramNo == 7 then
        g_HP7 = be:MDLgetHp()
        g_shield7 = 1
    end
elseif be:MDLisCallName("set") == 1 then
    if ramNo == 0 then
        g_HP0 = 0
        g_shield0 = 0
    elseif ramNo == 1 then
        g_HP1 = 0
        g_shield1 = 0
    elseif ramNo == 2 then
        g_HP2 = 0
        g_shield2 = 0
    elseif ramNo == 3 then
        g_HP3 = 0
        g_shield3 = 0
    elseif ramNo == 4 then
        g_HP4 = 0
        g_shield4 = 0
    elseif ramNo == 5 then
        g_HP5 = 0
        g_shield5 = 0
    elseif ramNo == 6 then
        g_HP6 = 0
        g_shield6 = 0
    elseif ramNo == 7 then
        g_HP7 = 0
        g_shield7 = 0
    end
end
