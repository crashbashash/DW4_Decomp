if be:MDLisCallName("WPos") then
    for local_10 = 1, local_6 do
        if local_7[local_10] == local_13 then
            if be:MDLgetHp() == 100 then
                be:MDLaddHp(local_14 + -100)
            end
            if be:MDLgetHp() == local_14 then
                local_0()
            elseif be:MDLgetHp() == local_15 then
                local_2()
            else
                local_1()
            end
            be:MDLsetWorldPosTarget(local_3[local_16], local_4[local_16], local_5[local_16])
        else
        end
    end
end
