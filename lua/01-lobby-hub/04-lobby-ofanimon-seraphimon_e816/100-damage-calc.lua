funcUp = function()
    be:MDLaddHp(1)
end
funcRandom = function() end
funcDown = function() end
if be:MDLisCallName("WPos") then
    for local_7 = 1, local_3 do
        if local_4[local_7] == local_10 then
            if be:MDLgetHp() == 100 then
                be:MDLaddHp(local_11 + -100)
            end
            if be:MDLgetHp() == local_11 then
                funcUp()
            elseif be:MDLgetHp() == local_12 then
                funcDown()
            else
                funcRandom()
            end
            be:MDLsetWorldPosTarget(local_0[local_13], local_1[local_13], local_2[local_13])
        else
        end
    end
end
