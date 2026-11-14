local sendTime = 270
if not g_mode then
    g_mode = 0
end
if not g_Ground then
    g_Ground = 0
end
if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetDMGTurn(0)
    local shootRamNo = be:BLTgetShootRamNo()
    be:sd("PLAYER", be:SYSgetPlayerName(shootRamNo), shootRamNo, "SQ_GUARDR", 0)
elseif be:BLTisHitCheck() == 0 then
    if g_Ground == 1 then
        be:MDLsetSeq("SQ_GUARD")
    end
else
    be:MDLsetDMGTurn(0)
    local isCritical = be:BLTisCritical()
    local damageValue = be:BLTgetDamageValue(isCritical)
    if damageValue == 0 then
        local time = 0
        if g_Ground == 1 and time == 0 then
            time = be:BLTgetSleepTime()
            if time > 0 then
                be:MDLsetSD("SETSLEEP", "I<" .. time .. ">")
            end
        end
        if g_Ground == 1 and time == 0 then
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
        if g_Ground == 1 then
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
        end
    elseif be:MDLgetHp() * 100 / be:MDLgetMHp() <= 66.6 and g_mode == 0 then
        be:sd("ENEMY", be:MDLgetInfoName(), be:MDLgetRamNo(), "CLEARSTATUS")
        be:MDLsetSeq("SQ_ENTY01")
        g_mode = g_mode + 1
    elseif be:MDLgetHp() * 100 / be:MDLgetMHp() <= 33.3 and g_mode == 1 then
        be:sd("ENEMY", be:MDLgetInfoName(), be:MDLgetRamNo(), "CLEARSTATUS")
        be:MDLsetSeq("SQ_ENTY02")
        g_mode = g_mode + 1
    else
        be:BLTcalcSkillUp(1, isCritical)
        if g_Ground == 1 then
            be:MDLaddHp(-damageValue)
            be:MDLdspDamage(damageValue)
            local damageRank = be:BLTgetDamageRank(be:MDLgetHp(), isCritical)
            if damageRank < 3 and be:MDLisStatus(be:MDLgetInfoName(), be:MDLgetRamNo(), "BIND") == 1 then
                be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_SDMG")
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
                be:BLTcalcEXPUp()
                local local_4
                local total = 0
                for playerIndex = 0, 3 do
                    if be:SYSisJoinPlayer(playerIndex) == 1 then
                        total = total + be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
                    end
                end
                if total ~= 0 then
                    be:sd("MODELCTRL", nil, -1, "OFCTRL")
                    if be:MDLisLive("i_bosshp03", 0) == 1 then
                        be:sd("MODELCTRL", "i_bosshp03", 0, "SQ_CLOSE")
                    end
                    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
                    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "dead", sendTime)
                    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
                    be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<60,10,10>/V<0,-90,0>")
                    be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<60,10,-10>/V<0,-90,0>")
                    be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<50,10,30>/V<0,-90,0>")
                    be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<50,10,-30>/V<0,-90,0>")
                    be:DMsetSD("MODELCTRL", "f_luce", 0, "MOVETRANS", "V<0,10,0>/V<0,90,0>")
                    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
                    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
                    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 20)
                    be:DMrun()
                    be:sd("SOUND", NULL, -1, "PLAY", "BT_WIN02", sendTime + 120)
                    be:sd("PLAYER", nil, -1, "SQ_ENJOY", sendTime + 210)
                    be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-23.75,10,-23.75>/V<0,45,0>/SQ_ENTR", sendTime + 330)
                    be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON", sendTime + 360)
                    be:sd("GENERATER", nil, -1, "START", "GBOX-01", sendTime + 330)
                    be:FLGset(69, 1)
                    if be:SYSgetDifficulty() > 0 then
                        be:FLGset(607, 1)
                    end
                    be:COUNTERset(2, 0)
                end
            end
        end
    end
    if g_Ground == 1 then
        if rank ~= 1 then
            if rank == 2 then
            end
        end
        local stunTime = be:BLTgetStunTime(damageValue, isCritical)
        if stunTime > 0 then
            be:MDLsetSD("SETSTUN", "I<" .. stunTime .. ">")
        end
    end
    if g_Ground == 1 and rank ~= 3 then
        local poisonTime = be:BLTgetPoisonTime("TIME")
        if poisonTime > 0 then
            local poisonTime2 = be:BLTgetPoisonTime("DAMAGE")
            be:MDLsetSD("SETPOISON", "I<" .. poisonTime .. ">/I<" .. poisonTime2 .. ">")
        end
    end
    if be:MDLisLive("i_bosshp03", 0) == 1 then
        be:sd("METERCTRL", "bshp03", 0, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
    end
end
