local bulletKind = be:MDLgetBulletKind()
local ramNo = be:MDLgetRamNo()
if bulletKind ~= 70126 then
    if bulletKind == 70127 then
    end
end
if ramNo ~= 0 then
    return
end
if bulletKind ~= 70128 then
    if bulletKind == 70129 then
    end
end
if ramNo ~= 1 then
    return
end
if bulletKind ~= 70130 then
    if bulletKind == 70131 then
    end
end
if ramNo ~= 2 then
    return
end
if bulletKind ~= 70132 then
    if bulletKind == 70133 then
    end
end
if ramNo ~= 3 then
    return
end
if 80000 <= bulletKind and bulletKind < 90000 then
    be:MDLsetDMGTurn(0)
    local effectMagic = be:BLPcalcKoukaMagic()
    be:BLTcalcSkillUp(effectMagic, 0)
else
    if be:MDLisSeqName("SQ_GUARD") ~= 1 then
        if be:BLPisHitCheck() == 0 then
        end
    end
    be:MDLsetSeq("SQ_GUARDR")
end
