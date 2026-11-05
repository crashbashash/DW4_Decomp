if not g_magic then
    g_magic = 0
end
if not g_switch then
    g_switch = 0
end
if not g_sw0 then
    g_sw0 = 0
end
if not g_sw1 then
    g_sw1 = 0
end
if not g_sw2 then
    g_sw2 = 0
end
if not g_sw3 then
    g_sw3 = 0
end
if not g_sw4 then
    g_sw4 = 0
end
if not g_sw5 then
    g_sw5 = 0
end
if not g_sw6 then
    g_sw6 = 0
end
if not g_sw7 then
    g_sw7 = 0
end
if not g_sw8 then
    g_sw8 = 0
end
if not g_sw9 then
    g_sw9 = 0
end
if not g_sw10 then
    g_sw10 = 0
end
if not g_sw11 then
    g_sw11 = 0
end
if be:MDLisCallName("stset") == 1 then
    if g_switch == 1 then
        g_switch = 0
    else
    end
end
if be:MDLisCallName("check") == 1 then
    for local_2 = 0, 11 do
        if be:MDLisLive("e_mummy", local_2) == 1 then
            local_0 = local_0 + 1
        end
    end
    if local_0 ~= 12 then
        be:sd("MODELCTRL", "e_pharaoh", be:MDLgetRamNo(), "SQ_ITEM1", 0)
    elseif local_0 == 12 then
        be:sd("MODELCTRL", "e_pharaoh", be:MDLgetRamNo(), "SQ_ITEM3", 0)
    end
elseif be:MDLisCallName("gen") == 1 then
    for local_1 = 0, 11 do
        if be:MDLisLive("e_mummy", local_1) == 0 then
            if be:SYSgetDifficulty() == 0 then
                be:sd("MODELCTRL", "e_mummy", local_1, "GENERATE", "SQ_NENTR/I<116>/I<149>/" .. be:MDLgetPosStr(0, 0, 0) .. "/" .. be:MDLgetRotStr(0, 0, 0))
            elseif be:SYSgetDifficulty() == 1 then
                be:sd("MODELCTRL", "e_mummy", local_1, "GENERATE", "SQ_NENTR/I<120>/I<896>/" .. be:MDLgetPosStr(0, 0, 0) .. "/" .. be:MDLgetRotStr(0, 0, 0))
            elseif be:SYSgetDifficulty() == 2 then
                be:sd("MODELCTRL", "e_mummy", local_1, "GENERATE", "SQ_NENTR/I<124>/I<2738>/" .. be:MDLgetPosStr(0, 0, 0) .. "/" .. be:MDLgetRotStr(0, 0, 0))
            end
        else
        end
    end
elseif be:MDLisCallName("mck") == 1 then
    for local_3 = 0, 11 do
        if be:MDLisLive("e_mummy", local_3) == 1 and g_magic == 1 and g_switch == 0 then
            local_1 = 1
        end
    end
    if local_0 ~= 12 and local_1 == 1 then
        g_switch = 1
        be:sd("MODELCTRL", "e_pharaoh", be:MDLgetRamNo(), "SQ_ITEM6", 0)
    elseif local_0 ~= 12 then
        be:sd("MODELCTRL", "e_pharaoh", be:MDLgetRamNo(), "SQ_ITEM5", 0)
    elseif local_1 == 1 then
        g_switch = 1
        be:sd("MODELCTRL", "e_pharaoh", be:MDLgetRamNo(), "SQ_MAGC", 0)
    else
        be:sd("MODELCTRL", "e_pharaoh", be:MDLgetRamNo(), "SQ_WAIT", 0)
    end
elseif be:MDLisCallName("magic") == 1 then
    for local_1 = 0, 11 do
        if be:MDLisLive("e_mummy", local_1) == 1 and g_magic == 1 and g_switch == 0 then
            g_switch = 1
            be:sd("MODELCTRL", "e_pharaoh", be:MDLgetRamNo(), "SQ_MAGC", 0)
        else
        end
    end
elseif be:MDLisCallName("reset") == 1 and g_magic == 1 and g_switch == 1 then
    g_switch = 0
    g_magic = 0
end
