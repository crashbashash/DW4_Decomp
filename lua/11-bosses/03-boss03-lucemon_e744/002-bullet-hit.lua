if not g_dmgf then
    g_dmgf = 0
end
if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetDMGTurn(0)
    be:sd("PLAYER", be:SYSgetPlayerName(local_0), local_0, "SQ_GUARDR", 0)
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetSeq("SQ_GUARD")
elseif local_1 == 0 then
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
    be:BLTcalcSkillUp(1, local_0)
    be:MDLaddHp(-local_1)
    be:MDLdspDamage(local_1)
    if local_2 == 0 then
        be:MDLsetSeq("SQ_DAMAGE")
        if be:SYSgetRandom(2) == 0 and g_Ground ~= 1 then
            g_dmgf = 1
        else
        end
    end
    if local_2 == 1 then
        be:MDLsetSeq("SQ_DAMAGE")
        if be:SYSgetRandom(2) == 1 and g_Ground ~= 1 then
            g_dmgf = 1
        else
        end
    end
    if local_2 == 2 then
        be:MDLsetSeq("SQ_DAMAGE")
    elseif local_2 == 3 then
        be:MDLsetSeq("SQ_EXIT")
        be:BLTcalcEXPUp()
    end
end
