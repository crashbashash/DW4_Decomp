if be:MDLisCallName("WPos") then
    for local_5 = 1, local_0 do
        if local_5 ~= 1 then
            if local_11 < local_2 then
                local_2 = local_11
                local_3 = local_5
            end
        end
        local_2 = local_11
        local_3 = local_5
    end
    be:MDLsetWorldPosTarget(local_1[local_5], local_1[local_6], local_1[local_7])
end
