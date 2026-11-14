if not g_DmgChk0 then
    g_DmgChk0 = 0
end
if not g_DmgChk1 then
    g_DmgChk1 = 0
end
if not g_DmgChk2 then
    g_DmgChk2 = 0
end
g_UFOPos = -1
if g_mecha4live < 1 and g_act == 1 and g_devlDmgChk == 0 then
    be:sd("MODELCTRL", "f_devl1", 0, "SQ_SWARPIN")
else
    local local_0
    local local_1 = 0
    for ramNo = 0, 2 do
        local_1 = 0
        if ramNo == 0 and g_DmgChk0 == 1 then
            local_1 = 1
        elseif ramNo == 1 and g_DmgChk1 == 1 then
            local_1 = 1
        elseif ramNo == 2 and g_DmgChk2 == 1 then
            local_1 = 1
        end
        if be:MDLisLive("e_mecha4bs", ramNo) == 1 and local_1 == 0 then
            be:sd("MODELCTRL", "e_mecha4bs", ramNo, "SQ_EXTEND", 0)
        end
    end
end
