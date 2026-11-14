if be:MDLisSeqName("SQ_HOVERON") == 1 then
    local local_0 = 8
    local list = {0, 53, 95, 67, 53, 67, 95, 53, 0, 67, 53, -67, 0, 53, -95, -67, 53, -67, -95, 53, 0, -67, 53, 67}
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
elseif be:MDLisSeqName("SQ_HOVERAI") == 1 then
    be:MDLsetWorldPosTarget(0, 53, 0)
else
    if be:MDLisSeqName("SQ_HOVER1") ~= 1 and be:MDLisSeqName("SQ_HOVER2") ~= 1 and be:MDLisSeqName("SQ_HOVER3") ~= 1 then
        if be:MDLisSeqName("SQ_HOVER4") == 1 then
        end
    end
    be:MDLsetWorldPosTarget(0, 53, 0)
end
