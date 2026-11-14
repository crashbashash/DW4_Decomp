if be:MDLisCallName("WPos") then
    local local_0 = 8
    local list = {-525, 10, -585, -115, 10, -585, -205, 10, -175, -365, 10, 295, -195, 10, 295, -365, 10, 465, -195, 10, 465, 5, 10, 505}
    local local_2
    local local_3
    local local_4
    for i = 1, local_0 do
        local local_8 = (i + -1) * 3 + 1
        local local_9 = (i + -1) * 3 + 2
        local local_10 = (i + -1) * 3 + 3
        local distanceSquare = be:MDLgetKyoriSquare(list[local_8], list[local_9], list[local_10])
        if i ~= 1 then
            if distanceSquare < local_2 then
            end
        end
        local_2 = distanceSquare
        local_3 = i
    end
    local local_5 = (local_3 + -1) * 3 + 1
    local local_6 = (local_3 + -1) * 3 + 2
    local local_7 = (local_3 + -1) * 3 + 3
    be:MDLsetWorldPosTarget(list[local_5], list[local_6], list[local_7])
end
