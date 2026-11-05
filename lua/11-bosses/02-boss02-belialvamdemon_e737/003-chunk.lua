if be:MDLisSeqName("SQ_HOVERON") == 1 then
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
elseif be:MDLisSeqName("SQ_HOVERAI") == 1 then
    be:MDLsetWorldPosTarget(0, 53, 0)
else
    if be:MDLisSeqName("SQ_HOVER1") ~= 1 and be:MDLisSeqName("SQ_HOVER2") ~= 1 and be:MDLisSeqName("SQ_HOVER3") ~= 1 then
        if be:MDLisSeqName("SQ_HOVER4") == 1 then
            be:MDLsetWorldPosTarget(0, 53, 0)
        elseif be:MDLisSeqName("SQ_ENTR") == 1 then
            be:MDLsetWorldPosTarget(0, 10, 50)
        end
    end
    be:MDLsetWorldPosTarget(0, 53, 0)
end
