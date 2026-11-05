if be:MATisPlayer() == 1 then
    local_1 = 0
    local_2 = 3
    for local_4 = 0, 3 do
        if be:MATisRidePlayer(local_4) == 1 and local_2 > local_4 then
            local_2 = local_4
        end
    end
    if local_1 == 1 then
        local_4 = be:PLAYERgetPosStr(local_2, 0, 0, 0)
        if g_fall0 == 1 then
            local_0(0, local_4, 0)
            g_fall0 = 0
        end
        if g_fall1 == 1 then
            local_0(1, local_4, 0)
            g_fall1 = 0
        end
        if g_fall2 == 1 then
            local_0(2, local_4, 0)
            g_fall2 = 0
        end
        if g_fall3 == 1 then
            local_0(3, local_4, 0)
            g_fall3 = 0
        end
        g_fallPos = 25
    end
end
