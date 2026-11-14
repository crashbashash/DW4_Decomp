if be:MDLgetBulletName() == "PCBA" then
    local shootRamNo = be:BLTgetShootRamNo()
    be:sd("PLAYER", be:SYSgetPlayerName(shootRamNo), shootRamNo, "SQ_GUARDR", 0)
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
                be:MDLsetSeq("SQ_BIND")
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
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SDMG")
        elseif damageRank == 0 then
            if be:SYSgetRandom(3) == 0 then
                be:MDLsetSD("SETLABEL", "SQ_WAIT/DMGJUMP")
            end
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SDMG")
        elseif damageRank == 1 then
            if be:SYSgetRandom(3) == 0 then
                be:MDLsetSD("SETLABEL", "SQ_WAIT/DMGJUMP")
            end
            be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_MDMG")
        elseif damageRank == 2 then
            if be:SYSgetRandom(3) == 0 then
                be:MDLsetSD("SETLABEL", "SQ_WAIT/DMGJUMP")
            end
            be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_LDMG")
        elseif damageRank == 3 then
            be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_DDMG")
            be:BLTcalcEXPUp()
            local local_3
            local total = 0
            for playerIndex = 0, 3 do
                if be:SYSisJoinPlayer(playerIndex) == 1 then
                    total = total + be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
                end
            end
            if total ~= 0 then
                be:sd("MODELCTRL", nil, -1, "OFCTRL")
                if be:MDLisLive("i_bosshp02", 0) == 1 then
                    be:sd("MODELCTRL", "i_bosshp02", 0, "SQ_CLOSE")
                end
                be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
                be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "dead", 120)
                be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
                be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-10,10,80>/V<0,180,0>")
                be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<10,10,80>/V<0,180,0>")
                be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-30,10,70>/V<0,180,0>")
                be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<30,10,70>/V<0,180,0>")
                be:DMsetSD("MODELCTRL", "f_belvam", 0, "MOVETRANS", "V<0,10,0>/V<0,0,0>")
                be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
                be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
                be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 0)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 20)
                be:DMrun()
                be:sd("SOUND", NULL, -1, "PLAY", "BT_WIN02", 240)
                be:sd("PLAYER", nil, -1, "SQ_ENJOY", 330)
                be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<0,10,-60>/V<0,0,0>/SQ_ENTR", 450)
                be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON", 480)
                be:sd("GENERATER", nil, -1, "START", "GBOX-01", 450)
                be:FLGset(68, 1)
                if be:SYSgetDifficulty() > 0 then
                    be:FLGset(603, 1)
                end
                be:COUNTERset(2, 0)
            end
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
        if be:MDLisLive("i_bosshp02", 0) == 1 then
            be:sd("METERCTRL", "bshp02", 0, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
        end
    end
end
