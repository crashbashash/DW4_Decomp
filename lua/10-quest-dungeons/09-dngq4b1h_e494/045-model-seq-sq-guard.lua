local bulletKind = be:MDLgetBulletKind()
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
