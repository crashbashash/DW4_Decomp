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
        if damageRank == 0 then
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
            local local_3
            local total = 0
            for playerIndex = 0, 3 do
                if be:SYSisJoinPlayer(playerIndex) == 1 then
                    total = total + be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
                end
            end
            if total ~= 0 then
                be:sd("MODELCTRL", nil, -1, "OFCTRL")
                if be:MDLisLive("i_bosshp01", 0) == 1 then
                    be:sd("MODELCTRL", "i_bosshp01", 0, "SQ_CLOSE")
                end
                for playerIndex = 0, 4 do
                    if be:MDLisLive("g_b01cpole", playerIndex) == 1 then
                        be:sd("MODELCTRL", "g_b01cpole", playerIndex, "SQ_DDMG")
                    end
                end
                if be:MDLisLive("f_bit", 0) == 1 then
                    be:sd("MODELCTRL", "f_bit", 0, "SQ_EXIT")
                end
                for playerIndex = 0, 4 do
                    be:sd("MODELCTRL", "g_b01dmgf1", playerIndex, "SQ_WAIT")
                    be:sd("MODELCTRL", "g_b01dmgf2", playerIndex, "SQ_SWOF")
                end
                be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
                be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "dead", 120)
                be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
                be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<80,20,10>/V<0,-90,0>")
                be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<80,20,-10>/V<0,-90,0>")
                be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<70,20,30>/V<0,-90,0>")
                be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<70,20,-30>/V<0,-90,0>")
                be:DMsetSD("MODELCTRL", "f_apocaly", 0, "MOVETRANS", "V<0,30,0>/V<0,90,0>")
                be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
                be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 0)
                be:DMsetSD("MODELCTRL", "g_b01base1", -1, "SQ_SWON")
                be:DMsetSD("MODELCTRL", "g_b01base2", -1, "SQ_SWON")
                be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 0)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 20)
                be:DMrun()
                be:sd("SOUND", NULL, -1, "PLAY", "BT_WIN02", 240)
                be:sd("PLAYER", nil, -1, "SQ_ENJOY", 330)
                be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-60,20,0>/V<0,90,0>/SQ_ENTR", 450)
                be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON", 480)
                be:sd("GENERATER", nil, -1, "START", "GBOX-01", 450)
                be:FLGset(67, 1)
                if be:SYSgetDifficulty() > 0 then
                    be:FLGset(600, 1)
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
        if be:MDLisLive("i_bosshp01", 0) == 1 then
            be:sd("METERCTRL", "bshp01", 0, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
        end
    end
end
