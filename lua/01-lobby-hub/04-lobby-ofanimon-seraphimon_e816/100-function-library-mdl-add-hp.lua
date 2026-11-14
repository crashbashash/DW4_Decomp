funcUp = function()
    be:MDLaddHp(1)
end
funcRandom = function()
    local random = be:SYSgetRandom(2)
    if random == 0 then
        be:MDLaddHp(1)
    else
        be:MDLaddHp(-1)
    end
end
funcDown = function()
    be:MDLaddHp(-1)
end
if be:MDLisCallName("WPos") then
    local list = {-50, -100, -50, -50, -50, -50, -100}
    local list2 = {10, 10, 10, 10, 10, 10, 10}
    local list3 = {80, 50, 50, 6, 94, 50, 50}
    local local_3 = 1
    local list4 = {0}
    local list5 = {1, 8}
    local local_6
    for i = 1, local_3 do
        local ramNo = be:MDLgetRamNo()
        if list4[i] == ramNo then
            local local_11 = list5[i]
            local local_12 = list5[i + 1] + -1
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
            local hp = be:MDLgetHp()
            be:MDLsetWorldPosTarget(list[hp], list2[hp], list3[hp])
        else
        end
    end
end
