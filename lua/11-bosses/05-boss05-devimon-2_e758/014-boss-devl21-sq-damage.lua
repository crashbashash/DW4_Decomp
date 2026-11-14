be:MDLsetDMGTurn(0)
local sendTime = 60
if not g_dev2mode then
    g_dev2mode = 0
end
if not g_headuphp then
    g_headuphp = be:MDLgetMHp() * 0.055
end
if not g_arm then
    g_arm = 1
end
if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetDMGTurn(0)
    local shootRamNo = be:BLTgetShootRamNo()
    be:sd("PLAYER", be:SYSgetPlayerName(shootRamNo), shootRamNo, "SQ_GUARDR", 0)
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetSeq("SQ_GUARD")
else
    be:MDLsetDMGTurn(0)
    local isCritical = be:BLTisCritical()
    local damage = be:BLTgetDamageValue(isCritical)
    if damage == 0 then
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
        if damage >= be:MDLgetMHp() * 0.12 then
            damage = be:MDLgetMHp() * 0.12
        end
        be:MDLaddHp(-damage)
        be:MDLdspDamage(damage)
        local local_3 = be:MDLgetHp() * 100 / be:MDLgetMHp()
        if g_dev2mode == 0 then
            if local_3 >= 94.1 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM0")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 >= 88.6 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM1")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 >= 83.1 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM2")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 >= 77.6 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM3")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 >= 72.1 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM4")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 >= 66.6 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM5")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            else
                be:MDLsetSeq("SQ_FIRE21")
                local local_4
                for ramNo = 0, 1 do
                    if be:MDLisLive("x_041fblst01a", ramNo) == 1 then
                        be:sd("MODELCTRL", "x_041fblst01a", ramNo, "SQ_ERAS")
                    end
                    if be:MDLisLive("f_devl24", ramNo) == 1 then
                        be:sd("MODELCTRL", "f_devl24", ramNo, "SQ_EXIT")
                    end
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 0 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_ENTR")
                    g_arm = 1
                else
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM6")
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_FIRESCALE", 10)
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_FIRESCALE", 10)
                end
                g_dev2mode = 1
            end
        elseif g_dev2mode == 1 then
            if local_3 >= 60.8 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM0")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 >= 55.3 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM1")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 >= 49.8 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM2")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 >= 44.3 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM3")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 >= 38.8 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM4")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 >= 33.3 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM5")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            else
                be:MDLsetSeq("SQ_FIRE21")
                local local_4
                for ramNo = 0, 1 do
                    if be:MDLisLive("x_041fblst01a", ramNo) == 1 then
                        be:sd("MODELCTRL", "x_041fblst01a", ramNo, "SQ_ERAS")
                    end
                    if be:MDLisLive("f_devl24", ramNo) == 1 then
                        be:sd("MODELCTRL", "f_devl24", ramNo, "SQ_EXIT")
                    end
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 0 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_ENTR")
                    g_arm = 1
                else
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM6")
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_FIRESCALE", 10)
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_FIRESCALE", 10)
                end
                g_dev2mode = 2
            end
        elseif g_dev2mode == 2 then
            if local_3 >= 27.5 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM0")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 >= 22 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM1")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 >= 16.5 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM2")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 >= 11 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM3")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 >= 5.5 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM4")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            elseif local_3 > 0 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM5")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
            else
                local local_4
                for ramNo = 0, 1 do
                    if be:MDLisLive("x_041fblst01a", ramNo) == 1 then
                        be:sd("MODELCTRL", "x_041fblst01a", ramNo, "SQ_ERAS")
                    end
                    if be:MDLisLive("f_devl24", ramNo) == 1 then
                        be:sd("MODELCTRL", "f_devl24", ramNo, "SQ_EXIT", 0)
                    end
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 0 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_ENTR", 0)
                    g_arm = 1
                else
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                end
                be:MDLsetSeq("SQ_MAEND")
                be:BLTcalcEXPUp()
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM6")
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_CHANGE", 10)
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_CHANGE", 10)
                end
                be:sd("MODELCTRL", "f_devl23", 0, "SQ_EXIT", 2)
                local local_5
                local total = 0
                for playerIndex = 0, 3 do
                    if be:SYSisJoinPlayer(playerIndex) == 1 then
                        total = total + be:SYSctlPlayer("HP", "GETHP", playerIndex, 0)
                    end
                end
                if total ~= 0 then
                    be:sd("MODELCTRL", nil, -1, "OFCTRL")
                    if be:MDLisLive("i_bosshp05", 0) == 1 then
                        be:sd("MODELCTRL", "i_bosshp05", 0, "SQ_CLOSE")
                    end
                    be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
                    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "dead", sendTime)
                    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
                    be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "d2FADE01")
                    be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-10,10,55>/V<0,180,0>")
                    be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<10,10,55>/V<0,180,0>")
                    be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-25,10,45>/V<0,180,0>")
                    be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<25,10,45>/V<0,180,0>")
                    be:DMsetSD("MODELCTRL", "g_dbossgate", 0, "GENERATE", "V<0,10,0>/V<0,0,0>/SQ_ENTR", 10)
                    be:DMsetSD("MODELCTRL", "g_dbossgate", 0, "SQ_POWERON", 300)
                    be:DMsetSD("MODELCTRL", "g_dbossgate", 0, "SQ_SWON", 360)
                    be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
                    be:DMsetSD("MODELCTRL", "g_dbossgate", 0, "SQ_SWOF")
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
                    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 20)
                    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
                    be:DMrun()
                end
            end
        end
        if rank ~= 1 then
            if rank == 2 then
            end
        end
        local stunTime = be:BLTgetStunTime(damage, isCritical)
        if stunTime > 0 then
            be:MDLsetSD("SETSTUN", "I<" .. stunTime .. ">")
        end
        if rank ~= 3 then
            local poisonTime = be:BLTgetPoisonTime("TIME")
            if poisonTime > 0 then
                local poisonTime2 = be:BLTgetPoisonTime("DAMAGE")
                be:MDLsetSD("SETPOISON", "I<" .. poisonTime .. ">/I<" .. poisonTime2 .. ">")
            end
        end
        if be:MDLisLive("i_bosshp05", 0) == 1 then
            be:sd("METERCTRL", "bshp05", 0, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
        end
    end
end
