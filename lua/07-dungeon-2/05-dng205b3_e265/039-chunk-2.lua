if not g_magic then
    g_magic = 0
end
if g_switch == 1 then
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
if be:MDLisCallName("request") == 1 then
    if g_magic == 0 and g_switch == 0 then
        g_magic = 1
        if local_0 == 0 then
            g_sw0 = 1
        elseif local_0 == 1 then
            g_sw1 = 1
        elseif local_0 == 2 then
            g_sw2 = 1
        elseif local_0 == 3 then
            g_sw3 = 1
        elseif local_0 == 4 then
            g_sw4 = 1
        elseif local_0 == 5 then
            g_sw5 = 1
        elseif local_0 == 6 then
            g_sw6 = 1
        elseif local_0 == 7 then
            g_sw7 = 1
        elseif local_0 == 8 then
            g_sw8 = 1
        elseif local_0 == 9 then
            g_sw9 = 1
        elseif local_0 == 10 then
            g_sw10 = 1
        elseif local_0 == 11 then
            g_sw11 = 1
        else
        end
    end
end
if be:MDLisCallName("reset") == 1 then
    if local_0 == 0 then
        g_sw0 = 0
    elseif local_0 == 1 then
        g_sw1 = 0
    elseif local_0 == 2 then
        g_sw2 = 0
    elseif local_0 == 3 then
        g_sw3 = 0
    elseif local_0 == 4 then
        g_sw4 = 0
    elseif local_0 == 5 then
        g_sw5 = 0
    elseif local_0 == 6 then
        g_sw6 = 0
    elseif local_0 == 7 then
        g_sw7 = 0
    elseif local_0 == 8 then
        g_sw8 = 0
    elseif local_0 == 9 then
        g_sw9 = 0
    elseif local_0 == 10 then
        g_sw10 = 0
    elseif local_0 == 11 then
        g_sw11 = 0
    end
end
