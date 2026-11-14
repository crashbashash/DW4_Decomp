if not g_RNo0 then
    g_RNo0 = 0
elseif not g_RNo1 then
    g_RNo1 = 0
elseif not g_RNo2 then
    g_RNo2 = 0
elseif not g_RNo3 then
    g_RNo3 = 0
end
local local_0 = 0
local ramNo = be:MDLgetRamNo()
if g_RNo0 == 1 and ramNo == 0 then
    local_0 = 1
elseif g_RNo1 == 1 and ramNo == 1 then
    local_0 = 1
elseif g_RNo2 == 1 and ramNo == 2 then
    local_0 = 1
elseif g_RNo3 == 1 and ramNo == 3 then
    local_0 = 1
end
if local_0 == 1 then
    if be:MDLgetBulletKind() >= 40035 and be:MDLgetBulletKind() <= 40039 then
        be:MDLsetSeq("SQ_SWOF")
    end
elseif be:MDLgetBulletName() == "PCBA" then
    be:MDLsetSeq("SQ_PUSHED")
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetSeq("SQ_GUARD")
else
    local isCritical = be:BLTisCritical()
    local damageValue = be:BLTgetDamageValue(isCritical)
    if damageValue == 0 then
        local time = 0
        if local_0 == 0 and time == 0 then
            time = be:BLTgetSleepTime()
            if time > 0 then
                be:MDLsetSD("SETSLEEP", "I<" .. time .. ">")
            end
        end
        if time == 0 then
            time = be:BLTgetBindTime()
            if time > 0 then
                be:MDLsetSD("SETBIND", "I<" .. time .. ">")
            end
        end
        if time == 0 then
            time = be:BLTgetAttackDownTime("TIME")
            if time > 0 then
                local attackDownTime = be:BLTgetAttackDownTime("SUBAYASA")
                local attackDownTime2 = be:BLTgetAttackDownTime("CHIMEIRITSU")
                local attackDownTime3 = be:BLTgetAttackDownTime("MAHIRITSU")
                local attackDownTime4 = be:BLTgetAttackDownTime("KAIHIRITSU")
                be:MDLsetSD("SETATTACKDOWN", "I<" .. time .. ">/I<" .. attackDownTime .. ">/I<" .. attackDownTime2 .. ">/I<" .. attackDownTime3 .. ">/I<" .. attackDownTime4 .. ">")
            end
        end
        if time == 0 then
            time = be:BLTgetPowerDownTime("TIME")
            if time > 0 then
                local powerDownTime = be:BLTgetPowerDownTime("TSUYOSA")
                local powerDownTime2 = be:BLTgetPowerDownTime("MAMORI")
                be:MDLsetSD("SETPOWERDOWN", "I<" .. time .. ">/I<" .. powerDownTime .. ">/I<" .. powerDownTime2 .. ">")
            end
        end
        if time == 0 then
            be:MDLsetSeq("SQ_GUARD")
            be:BLTcalcSkillUp(0, 0)
        elseif time < 0 then
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
        if damageRank < 3 and be:MDLisStatus(be:MDLgetInfoName(), be:MDLgetRamNo(), "BIND") == 1 then
            if be:MDLgetHp() < be:MDLgetMHp() / 2 and be:MDLgetHp() + damageValue >= be:MDLgetMHp() / 2 then
                be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_SCNTDMG")
            else
                be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_SDMG")
            end
        elseif damageRank < 3 and be:MDLgetHp() < be:MDLgetMHp() / 2 and be:MDLgetHp() + damageValue >= be:MDLgetMHp() / 2 then
            if damageRank == 0 then
                be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_SCNTDMG")
            elseif damageRank == 1 then
                be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_MCNTDMG")
            elseif damageRank == 2 then
                be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_LCNTDMG")
            end
        elseif damageRank == 0 then
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SDMG")
        elseif damageRank == 1 then
            be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_MDMG")
        elseif damageRank == 2 then
            be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_LDMG")
        elseif damageRank == 3 then
            be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_DDMG")
            be:MDLdspExp(be:BLTcalcEXPUp())
        end
        if local_0 == 0 then
            if damageRank ~= 1 then
                if damageRank == 2 then
                end
            end
            local stunTime = be:BLTgetStunTime(damageValue, isCritical)
            if stunTime > 0 then
                be:MDLsetSD("SETSTUN", "I<" .. stunTime .. ">")
            end
        end
        if damageRank ~= 3 then
            local poisonTime = be:BLTgetPoisonTime("TIME")
            if poisonTime > 0 then
                local poisonTime2 = be:BLTgetPoisonTime("DAMAGE")
                be:MDLsetSD("SETPOISON", "I<" .. poisonTime .. ">/I<" .. poisonTime2 .. ">")
            end
        end
    end
end
