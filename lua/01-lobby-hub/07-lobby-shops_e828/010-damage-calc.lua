local addHp = function()
    be:MDLaddHp(1)
end
local addHp2 = function()
    local random = be:SYSgetRandom(2)
    if random == 0 then
        be:MDLaddHp(1)
    else
        be:MDLaddHp(-1)
    end
end
local addHp3 = function()
    be:MDLaddHp(-1)
end
if be:MDLisCallName("WPos") then
    local list = {150, 200, 200, 150}
    local list2 = {40, 40, 40, 40}
    local list3 = {190, 240, 280, 330}
    local local_6 = 1
    local list4 = {0}
    local list5 = {1, 5}
    local local_9
    for i = 1, local_6 do
        local ramNo = be:MDLgetRamNo()
        if list4[i] == ramNo then
            local local_14 = list5[i]
            local local_15 = list5[i + 1] + -1
            if be:MDLgetHp() == 100 then
                be:MDLaddHp(local_14 + -100)
            end
            if be:MDLgetHp() == local_14 then
                addHp()
            elseif be:MDLgetHp() == local_15 then
                addHp3()
            else
                addHp2()
            end
            local hp = be:MDLgetHp()
            be:MDLsetWorldPosTarget(list[hp], list2[hp], list3[hp])
        else
        end
    end
end
