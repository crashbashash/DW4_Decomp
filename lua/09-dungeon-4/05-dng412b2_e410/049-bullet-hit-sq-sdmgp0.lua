local shootRamNo = be:BLTgetShootRamNo()
if not g_HP0 then
    g_HP0 = 0
end
if not g_HP1 then
    g_HP1 = 0
end
if not g_HP2 then
    g_HP2 = 0
end
if not g_HP3 then
    g_HP3 = 0
end
if not g_HP4 then
    g_HP4 = 0
end
if not g_HP5 then
    g_HP5 = 0
end
if not g_HP6 then
    g_HP6 = 0
end
if not g_HP7 then
    g_HP7 = 0
end
if not g_shield0 then
    g_shield0 = 0
end
if not g_shield1 then
    g_shield1 = 0
end
if not g_shield2 then
    g_shield2 = 0
end
if not g_shield3 then
    g_shield3 = 0
end
if not g_shield4 then
    g_shield4 = 0
end
if not g_shield5 then
    g_shield5 = 0
end
if not g_shield6 then
    g_shield6 = 0
end
if not g_shield7 then
    g_shield7 = 0
end
local local_1 = 0
local local_2 = 0
local ramNo = be:MDLgetRamNo()
if ramNo == 0 then
    local_1 = g_HP0
    local_2 = g_shield0
elseif ramNo == 1 then
    local_1 = g_HP1
    local_2 = g_shield1
elseif ramNo == 2 then
    local_1 = g_HP2
    local_2 = g_shield2
elseif ramNo == 3 then
    local_1 = g_HP3
    local_2 = g_shield3
elseif ramNo == 4 then
    local_1 = g_HP4
    local_2 = g_shield4
elseif ramNo == 5 then
    local_1 = g_HP5
    local_2 = g_shield5
elseif ramNo == 6 then
    local_1 = g_HP6
    local_2 = g_shield6
elseif ramNo == 7 then
    local_1 = g_HP7
    local_2 = g_shield7
end
if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetSeq("SQ_PUSHED")
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetSeq("SQ_GUARD")
else
    local isCritical = be:BLTisCritical()
    local damageValue = be:BLTgetDamageValue(isCritical)
    if damageValue == 0 then
        local time = 0
        if time == 0 then
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
        local local_7 = local_1 - be:MDLgetMHp() * 0.3
        if damageRank < 3 and be:MDLisStatus(be:MDLgetInfoName(), be:MDLgetRamNo(), "BIND") == 1 then
            if be:MDLgetHp() <= local_7 then
                be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_SCALL")
            elseif local_2 == 1 then
                if shootRamNo == 0 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP0")
                elseif shootRamNo == 1 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP1")
                elseif shootRamNo == 2 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP2")
                elseif shootRamNo == 3 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP3")
                end
            else
                be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_SDMG")
            end
        elseif damageRank == 0 then
            if be:MDLgetHp() <= local_7 then
                be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_SCALL")
            elseif local_2 == 1 then
                if shootRamNo == 0 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP0")
                elseif shootRamNo == 1 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP1")
                elseif shootRamNo == 2 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP2")
                elseif shootRamNo == 3 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP3")
                end
            else
                be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_SDMG")
            end
        elseif damageRank == 1 then
            if be:MDLgetHp() <= local_7 then
                be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_MCALL")
            elseif local_2 == 1 then
                if shootRamNo == 0 then
                    be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_MDMGP0")
                elseif shootRamNo == 1 then
                    be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_MDMGP1")
                elseif shootRamNo == 2 then
                    be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_MDMGP2")
                elseif shootRamNo == 3 then
                    be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_MDMGP3")
                end
            else
                be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_MDMG")
            end
        elseif damageRank == 2 then
            if be:MDLgetHp() <= local_7 then
                be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_LCALL")
            elseif local_2 == 1 then
                if shootRamNo == 0 then
                    be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_LDMGP0")
                elseif shootRamNo == 1 then
                    be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_LDMGP1")
                elseif shootRamNo == 2 then
                    be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_LDMGP2")
                elseif shootRamNo == 3 then
                    be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_LDMGP3")
                end
            else
                be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_LDMG")
            end
        elseif damageRank == 3 then
            if local_2 == 1 then
                if shootRamNo == 0 then
                    be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_DDMGP0")
                elseif shootRamNo == 1 then
                    be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_DDMGP1")
                elseif shootRamNo == 2 then
                    be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_DDMGP2")
                elseif shootRamNo == 3 then
                    be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_DDMGP3")
                end
            else
                be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_DDMG")
            end
            be:MDLdspExp(be:BLTcalcEXPUp())
        end
        if damageRank ~= 1 then
            if damageRank == 2 then
            end
        end
        local stunTime = be:BLTgetStunTime(damageValue, isCritical)
        if stunTime > 0 then
            be:MDLsetSD("SETSTUN", "I<" .. stunTime .. ">")
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
