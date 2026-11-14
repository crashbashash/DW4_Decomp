be:MDLsetDMGTurn(0)
local shootRamNo = be:BLTgetShootRamNo()
local ramNo = be:MDLgetRamNo()
local local_2 = 0
if not g_Rocksh0 then
    g_Rocksh0 = 0
end
if not g_Rocksh1 then
    g_Rocksh1 = 0
end
if not g_Rocksh2 then
    g_Rocksh2 = 0
end
if not g_Rocksh3 then
    g_Rocksh3 = 0
end
if g_Rocksh0 == 1 and ramNo == 0 then
    local_2 = 1
elseif g_Rocksh1 == 1 and ramNo == 1 then
    local_2 = 1
elseif g_Rocksh2 == 1 and ramNo == 2 then
    local_2 = 1
elseif g_Rocksh3 == 1 and ramNo == 3 then
    local_2 = 1
end
local local_3 = 0
if local_3 == 0 and local_2 == 1 and be:MDLgetBulletBoxNo() == 0 then
    if be:MDLgetBulletKind() >= 40040 and be:MDLgetBulletKind() <= 40090 then
        be:MDLsetSeq("SQ_WAIT")
        local_3 = 1
        be:BLTcalcSkillUp(0, 0)
    elseif be:MDLgetBulletName() == "PCBA" then
        be:MDLsetDMGTurn(0)
        local shootRamNo2 = be:BLTgetShootRamNo()
        be:sd("PLAYER", be:SYSgetPlayerName(shootRamNo2), shootRamNo2, "SQ_GUARDR", 0)
        local_3 = 1
    end
end
if local_3 == 0 and local_2 == 1 then
    if be:MDLgetBulletBoxNo() ~= 1 then
        if be:MDLgetBulletBoxNo() == 2 then
        end
    end
    if be:MDLgetBulletKind() < 40035 then
        if shootRamNo == 0 then
            be:MDLsetSeq("SQ_DMGP0")
            local_3 = 1
        elseif shootRamNo == 1 then
            be:MDLsetSeq("SQ_DMGP1")
            local_3 = 1
        elseif shootRamNo == 2 then
            be:MDLsetSeq("SQ_DMGP2")
            local_3 = 1
        elseif shootRamNo == 3 then
            be:MDLsetSeq("SQ_DMGP3")
            local_3 = 1
        end
    elseif be:MDLgetBulletKind() >= 40040 and be:MDLgetBulletKind() <= 40090 then
        be:MDLsetSeq("SQ_WAIT")
        local_3 = 1
        be:BLTcalcSkillUp(0, 0)
    end
end
if local_3 == 0 then
    if be:MDLgetBulletName() == "PCBA" then
        be:MDLsetDMGTurn(0)
        local shootRamNo2 = be:BLTgetShootRamNo()
        be:sd("PLAYER", be:SYSgetPlayerName(shootRamNo2), shootRamNo2, "SQ_GUARDR", 0)
        local_3 = 1
    elseif be:BLTisHitCheck() == 0 then
        be:MDLsetSeq("SQ_GUARD")
        local_3 = 1
    else
        local isCritical = be:BLTisCritical()
        local damageValue = be:BLTgetDamageValue(isCritical)
        if damageValue == 0 then
            local local_6 = 0
            if local_6 == 0 then
                local_6 = be:BLTgetSleepTime()
                if local_6 > 0 then
                    if local_2 ~= 1 then
                        be:MDLsetSD("SETSLEEP", "I<" .. local_6 .. ">")
                    else
                        local_6 = -1
                    end
                end
            end
            if local_6 == 0 then
                local_6 = be:BLTgetBindTime()
                if local_6 > 0 then
                    if local_2 ~= 1 then
                        be:MDLsetSD("SETBIND", "I<" .. local_6 .. ">")
                    else
                        local_6 = -1
                    end
                end
            end
            if local_6 == 0 then
                local_6 = be:BLTgetAttackDownTime("TIME")
                if local_6 > 0 then
                    if local_2 ~= 1 then
                        local attackDownTime = be:BLTgetAttackDownTime("SUBAYASA")
                        local attackDownTime2 = be:BLTgetAttackDownTime("CHIMEIRITSU")
                        local attackDownTime3 = be:BLTgetAttackDownTime("MAHIRITSU")
                        local attackDownTime4 = be:BLTgetAttackDownTime("KAIHIRITSU")
                        be:MDLsetSD("SETATTACKDOWN", "I<" .. local_6 .. ">/I<" .. attackDownTime .. ">/I<" .. attackDownTime2 .. ">/I<" .. attackDownTime3 .. ">/I<" .. attackDownTime4 .. ">")
                    else
                        local_6 = -1
                    end
                end
            end
            if local_6 == 0 then
                local_6 = be:BLTgetPowerDownTime("TIME")
                if local_6 > 0 then
                    if local_2 ~= 1 then
                        local powerDownTime = be:BLTgetPowerDownTime("TSUYOSA")
                        local powerDownTime2 = be:BLTgetPowerDownTime("MAMORI")
                        be:MDLsetSD("SETPOWERDOWN", "I<" .. local_6 .. ">/I<" .. powerDownTime .. ">/I<" .. powerDownTime2 .. ">")
                    else
                        local_6 = -1
                    end
                end
            end
            if local_6 == 0 then
                if local_2 ~= 1 then
                    be:MDLsetSeq("SQ_GUARD")
                    be:BLTcalcSkillUp(0, 0)
                elseif local_2 == 1 and be:MDLgetBulletBoxNo() == 0 then
                    be:MDLsetDMGTurn(0)
                    be:MDLsetSeq("SQ_DMGOF")
                    local_3 = 1
                end
            elseif local_6 < 0 then
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
                if local_2 == 1 and be:MDLgetBulletBoxNo() == 0 then
                    be:MDLsetSeq("SQ_DMGOF")
                    local_3 = 1
                elseif local_2 == 1 and be:MDLgetBulletKind() >= 40035 and be:MDLgetBulletKind() <= 40039 then
                    be:MDLsetSeq("SQ_DMGOF")
                    local_3 = 1
                else
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMG")
                    local_3 = 1
                end
            elseif damageRank == 0 then
                if local_2 == 1 and be:MDLgetBulletBoxNo() == 0 then
                    be:MDLsetSeq("SQ_DMGOF")
                    local_3 = 1
                elseif local_2 == 1 and be:MDLgetBulletKind() >= 40035 and be:MDLgetBulletKind() <= 40039 then
                    be:MDLsetSeq("SQ_DMGOF")
                    local_3 = 1
                else
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMG")
                    local_3 = 1
                end
            elseif damageRank == 1 then
                if local_2 == 1 and be:MDLgetBulletBoxNo() == 0 then
                    be:MDLsetSeq("SQ_DMGOF")
                    local_3 = 1
                elseif local_2 == 1 and be:MDLgetBulletKind() >= 40035 and be:MDLgetBulletKind() <= 40039 then
                    be:MDLsetSeq("SQ_DMGOF")
                    local_3 = 1
                else
                    be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_MDMG")
                    local_3 = 1
                end
            elseif damageRank == 2 then
                if local_2 == 1 and be:MDLgetBulletBoxNo() == 0 then
                    be:MDLsetSeq("SQ_DMGOF")
                    local_3 = 1
                elseif local_2 == 1 and be:MDLgetBulletKind() >= 40035 and be:MDLgetBulletKind() <= 40039 then
                    be:MDLsetSeq("SQ_DMGOF")
                    local_3 = 1
                else
                    be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_LDMG")
                    local_3 = 1
                end
            elseif damageRank == 3 then
                if local_2 == 1 then
                    be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_DDMG")
                    local_3 = 1
                else
                    be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_DDMG")
                    local_3 = 1
                end
                be:MDLdspExp(be:BLTcalcEXPUp())
                local_3 = 1
                if be:MDLisLive("i_bosshp16", 0) == 1 then
                    be:sd("MODELCTRL", "i_bosshp16", 0, "SQ_CLOSE")
                end
            end
            if local_2 == 0 then
                if damageRank ~= 1 then
                    if damageRank == 2 then
                    end
                end
                local stunTime = be:BLTgetStunTime(damageValue, isCritical)
                if stunTime > 0 then
                    be:MDLsetSD("SETSTUN", "I<" .. stunTime .. ">")
                end
            end
            if local_2 == 0 and damageRank ~= 3 then
                local poisonTime = be:BLTgetPoisonTime("TIME")
                if poisonTime > 0 then
                    local poisonTime2 = be:BLTgetPoisonTime("DAMAGE")
                    be:MDLsetSD("SETPOISON", "I<" .. poisonTime .. ">/I<" .. poisonTime2 .. ">")
                end
            end
            if be:MDLisLive("i_bosshp16", 0) == 1 then
                be:sd("METERCTRL", "bshp16", 0, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
            end
        end
    end
end
