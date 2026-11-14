if not g_dmgf then
    g_dmgf = 0
end
if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetDMGTurn(0)
    local shootRamNo = be:BLTgetShootRamNo()
    be:sd("PLAYER", be:SYSgetPlayerName(shootRamNo), shootRamNo, "SQ_GUARDR", 0)
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetSeq("SQ_GUARD")
else
    local isCritical = be:BLTisCritical()
    local damageValue = be:BLTgetDamageValue(isCritical)
    if damageValue == 0 then
        local local_2 = 0
        if local_2 == 0 then
            be:MDLsetSeq("SQ_GUARD")
            be:BLTcalcSkillUp(0, 0)
        elseif local_2 < 0 then
            be:MDLsetDMGTurn(0)
            be:BLTcalcSkillUp(0, 0)
        else
            be:MDLsetDMGTurn(0)
            be:BLTcalcSkillUp(1, 0)
        end
    else
        be:BLTcalcSkillUp(1, isCritical)
        be:MDLaddHp(-damageValue)
        be:MDLdspDamage(damageValue)
        local damageRank = be:BLTgetDamageRank(be:MDLgetHp(), isCritical)
        if damageRank == 0 then
            be:MDLsetSeq("SQ_DAMAGE")
            if be:SYSgetRandom(2) == 0 and g_Ground ~= 1 then
                g_dmgf = 1
            end
        elseif damageRank == 1 then
            be:MDLsetSeq("SQ_DAMAGE")
            if be:SYSgetRandom(2) == 1 and g_Ground ~= 1 then
                g_dmgf = 1
            end
        elseif damageRank == 2 then
            be:MDLsetSeq("SQ_DAMAGE")
        elseif damageRank == 3 then
            be:MDLsetSeq("SQ_EXIT")
            be:BLTcalcEXPUp()
        end
    end
end
