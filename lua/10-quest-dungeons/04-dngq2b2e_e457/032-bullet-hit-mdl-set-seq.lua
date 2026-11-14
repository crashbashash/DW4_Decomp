if not g_magic then
    g_magic = 0
end
if not g_switch then
    g_switch = 0
end
if not g_sw0 then
    g_sw0 = 0
end
if not g_sw1 then
    g_sw1 = 0
end
if not g_sw2 then
    g_sw2 = 0
end
if not g_sw3 then
    g_sw3 = 0
end
if not g_sw4 then
    g_sw4 = 0
end
if not g_sw5 then
    g_sw5 = 0
end
if not g_sw6 then
    g_sw6 = 0
end
if not g_sw7 then
    g_sw7 = 0
end
if not g_sw8 then
    g_sw8 = 0
end
if not g_sw9 then
    g_sw9 = 0
end
if not g_sw10 then
    g_sw10 = 0
end
if not g_sw11 then
    g_sw11 = 0
end
local ramNo = be:MDLgetRamNo()
local local_1 = 0
if ramNo == 0 then
    if g_sw0 == 1 then
        g_sw0 = 2
        local_1 = 1
    elseif g_sw0 == 2 then
        local_1 = 2
    end
elseif ramNo == 1 then
    if g_sw1 == 1 then
        g_sw1 = 2
        local_1 = 1
    elseif g_sw1 == 2 then
        local_1 = 2
    end
elseif ramNo == 2 then
    if g_sw2 == 1 then
        g_sw2 = 2
        local_1 = 1
    elseif g_sw2 == 2 then
        local_1 = 2
    end
elseif ramNo == 3 then
    if g_sw3 == 1 then
        g_sw3 = 2
        local_1 = 1
    elseif g_sw3 == 2 then
        local_1 = 2
    end
elseif ramNo == 4 then
    if g_sw4 == 1 then
        g_sw4 = 2
        local_1 = 1
    elseif g_sw4 == 2 then
        local_1 = 2
    end
elseif ramNo == 5 then
    if g_sw5 == 1 then
        g_sw5 = 2
        local_1 = 1
    elseif g_sw5 == 2 then
        local_1 = 2
    end
elseif ramNo == 6 then
    if g_sw6 == 1 then
        g_sw6 = 2
        local_1 = 1
    elseif g_sw6 == 2 then
        local_1 = 2
    end
elseif ramNo == 7 then
    if g_sw7 == 1 then
        g_sw7 = 2
        local_1 = 1
    elseif g_sw7 == 2 then
        local_1 = 2
    end
elseif ramNo == 8 then
    if g_sw8 == 1 then
        g_sw8 = 2
        local_1 = 1
    elseif g_sw8 == 2 then
        local_1 = 2
    end
elseif ramNo == 9 then
    if g_sw9 == 1 then
        g_sw9 = 2
        local_1 = 1
    elseif g_sw9 == 2 then
        local_1 = 2
    end
elseif ramNo == 10 then
    if g_sw10 == 1 then
        g_sw10 = 2
        local_1 = 1
    elseif g_sw10 == 2 then
        local_1 = 2
    end
elseif ramNo == 11 then
    if g_sw11 == 1 then
        g_sw11 = 2
        local_1 = 1
    elseif g_sw11 == 2 then
        local_1 = 2
    end
end
if be:MDLgetBulletKind() == 90123 then
    be:MDLsetSeq("SQ_SWON")
elseif be:MDLgetBulletKind() == 90026 then
    if local_1 == 1 and g_switch == 1 then
        be:MDLaddHp(be:MDLgetMHp() / 2)
        be:MDLsetSeq("SQ_RECV")
    else
        be:MDLsetSeq("SQ_NRECV")
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
        if damageRank < 3 and be:MDLisStatus(be:MDLgetInfoName(), be:MDLgetRamNo(), "BIND") == 1 then
            if be:MDLgetHp() < be:MDLgetMHp() * 0.6 and be:MDLgetHp() + damageValue >= be:MDLgetMHp() * 0.6 then
                be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_SMAGC")
            elseif be:MDLgetHp() < be:MDLgetMHp() * 0.3 and be:MDLgetHp() + damageValue >= be:MDLgetMHp() * 0.3 then
                be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_SDMG")
            else
                be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_SDMG")
            end
        elseif damageRank < 3 and be:MDLgetHp() < be:MDLgetMHp() * 0.6 and be:MDLgetHp() + damageValue >= be:MDLgetMHp() * 0.6 then
            be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_LMAGC")
        elseif damageRank < 3 and be:MDLgetHp() < be:MDLgetMHp() * 0.3 and be:MDLgetHp() + damageValue >= be:MDLgetMHp() * 0.3 then
            be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_LDMG")
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
            if be:BLTgetShootRamNo() == 0 then
                local local_5 = be:COUNTERget(3) + 1
                be:COUNTERset(3, local_5)
                be:sd("NUMBERCTRL", "questnm0", 0, "SETVALUE", "I<" .. be:COUNTERget(3) .. ">")
            elseif be:BLTgetShootRamNo() == 1 then
                local local_5 = be:COUNTERget(4) + 1
                be:COUNTERset(4, local_5)
                be:sd("NUMBERCTRL", "questnm0", 1, "SETVALUE", "I<" .. be:COUNTERget(4) .. ">")
            elseif be:BLTgetShootRamNo() == 2 then
                local local_5 = be:COUNTERget(5) + 1
                be:COUNTERset(5, local_5)
                be:sd("NUMBERCTRL", "questnm0", 2, "SETVALUE", "I<" .. be:COUNTERget(5) .. ">")
            elseif be:BLTgetShootRamNo() == 3 then
                local local_5 = be:COUNTERget(6) + 1
                be:COUNTERset(6, local_5)
                be:sd("NUMBERCTRL", "questnm0", 3, "SETVALUE", "I<" .. be:COUNTERget(6) .. ">")
            end
            g_counter_total = be:COUNTERget(3) + be:COUNTERget(4) + be:COUNTERget(5) + be:COUNTERget(6)
            be:sd("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. g_counter_total .. ">")
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
