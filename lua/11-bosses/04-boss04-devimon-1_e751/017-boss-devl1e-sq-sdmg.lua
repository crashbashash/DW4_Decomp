local local_0 = 0
local local_1 = 0
local sendTime = 60
if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetDMGTurn(0)
    local shootRamNo = be:BLTgetShootRamNo()
    be:sd("PLAYER", be:SYSgetPlayerName(shootRamNo), shootRamNo, "SQ_GUARDR", 0)
elseif be:BLTisHitCheck() == 0 then
    if g_act ~= 1 then
        if g_act == 2 then
        end
    end
    be:MDLsetSeq("SQ_GUARD")
else
    be:MDLsetDMGTurn(0)
    local isCritical = be:BLTisCritical()
    local damageValue = be:BLTgetDamageValue(isCritical)
    if damageValue == 0 then
        local time = 0
        if g_act ~= 1 then
            if g_act == 2 then
            end
        end
        if time == 0 then
            time = be:BLTgetSleepTime()
            if time > 0 then
                be:MDLsetSD("SETSLEEP", "I<" .. time .. ">")
            end
        end
        if g_act == 2 and time == 0 then
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
        if g_act ~= 1 then
            if g_act == 2 then
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
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SDMG")
        elseif damageRank == 1 then
            be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_MDMG")
        elseif damageRank == 2 then
            be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_LDMG")
        elseif damageRank == 3 then
            g_devlDmgChk = 1
            if g_act == 3 then
                g_act = 2
                be:sd("MODELCTRL", "f_devl1e", 0, "SQ_WAIT")
            end
            local local_6
            local total = 0
            for playerIndex = 0, 3 do
                if be:SYSisJoinPlayer(playerIndex) == 1 then
                    total = total + be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
                end
            end
            if total == 0 then
                be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_LDMG")
                return
            end
            for playerIndex = 0, 2 do
                if be:MDLisLive("f_devl1b", playerIndex) == 1 then
                    be:sd("ENEMY", be:MDLgetInfoName(), be:MDLgetRamNo(), "CLEARSTATUS")
                    be:MDLsetSeq("SQ_CHADMG")
                    be:sd("MODELCTRL", "f_devl1b", playerIndex, "SQ_CHADMG")
                    local_1 = 1
                else
                end
            end
            if local_1 == 0 then
                be:sd("MODELCTRL", nil, -1, "OFCTRL")
                if be:MDLisLive("i_bosshp04", 0) == 1 then
                    be:sd("MODELCTRL", "i_bosshp04", 0, "SQ_CLOSE")
                end
                be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_DDMG")
                be:MDLdspExp(be:BLTcalcEXPUp())
                be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
                for playerIndex = 0, 2 do
                    if be:MDLisLive("e_mecha4bs", playerIndex) == 1 then
                        be:sd("MODELCTRL", "e_mecha4bs", playerIndex, "SQ_ERAS")
                    end
                end
                if be:MDLisLive("f_devl1c", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl1c", 0, "SQ_ERAS")
                end
                be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "dead", sendTime)
                be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
                be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "d1FADE01")
                be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-10,10,80>/V<0,180,0>")
                be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<10,10,80>/V<0,180,0>")
                be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-30,10,70>/V<0,180,0>")
                be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<30,10,70>/V<0,180,0>")
                be:DMsetSD("MODELCTRL", "f_devl1", 0, "MOVETRANS", "V<0,10,0>/V<0,0,0>")
                be:DMsetSD("MODELCTRL", "g_dbossgate", 0, "GENERATE", "V<0,10,-80>/V<0,0,0>/SQ_ENTR", 10)
                be:DMsetSD("MODELCTRL", "g_dbossgate", 0, "SQ_POWERON", 300)
                be:DMsetSD("MODELCTRL", "g_dbossgate", 0, "SQ_SWON", 360)
                be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
                be:DMsetSD("MODELCTRL", "g_dbossgate", 0, "SQ_SWOF")
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
                be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
                be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 20)
                be:DMrun()
            end
        end
        if g_act ~= 1 then
            if g_act == 2 then
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
        if be:MDLisLive("i_bosshp04", 0) == 1 then
            be:sd("METERCTRL", "bshp04", 0, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
        end
    end
end
