be:MDLsetDMGTurn(0)
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
    be:sd("PLAYER", be:SYSgetPlayerName(local_1), local_1, "SQ_GUARDR", 0)
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetSeq("SQ_GUARD")
else
    be:MDLsetDMGTurn(0)
    if local_2 == 0 then
        if local_3 == 0 and local_3 > 0 then
            be:MDLsetSD("SETSLEEP", "I<" .. local_3 .. ">")
        end
        if local_3 == 0 and local_3 > 0 then
            be:MDLsetSD("SETBIND", "I<" .. local_3 .. ">")
        end
        if local_3 == 0 and local_3 > 0 then
            be:MDLsetSD("SETATTACKDOWN", "I<" .. local_3 .. ">/I<" .. local_4 .. ">/I<" .. local_5 .. ">/I<" .. local_6 .. ">/I<" .. local_7 .. ">")
        end
        if local_3 == 0 and local_3 > 0 then
            be:MDLsetSD("SETPOWERDOWN", "I<" .. local_3 .. ">/I<" .. local_4 .. ">/I<" .. local_5 .. ">")
        end
        if local_3 == 0 then
            be:MDLsetSeq("SQ_GUARD")
            be:BLTcalcSkillUp(0, 0)
        elseif local_3 < 0 then
            be:MDLsetDMGTurn(0)
            be:BLTcalcSkillUp(0, 0)
        else
            be:MDLsetDMGTurn(0)
            be:BLTcalcSkillUp(1, 0)
        end
    else
        be:BLTcalcSkillUp(1, local_1)
        if local_2 >= be:MDLgetMHp() * 0.12 then
            local_2 = be:MDLgetMHp() * 0.12
        end
        be:MDLaddHp(-local_2)
        be:MDLdspDamage(local_2)
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
                else
                end
            end
            if local_3 >= 88.6 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM1")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            if local_3 >= 83.1 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM2")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            if local_3 >= 77.6 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM3")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            if local_3 >= 72.1 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM4")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            if local_3 >= 66.6 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM5")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            be:MDLsetSeq("SQ_FIRE21")
            for local_5 = 0, 1 do
                if be:MDLisLive("x_041fblst01a", local_5) == 1 then
                    be:sd("MODELCTRL", "x_041fblst01a", local_5, "SQ_ERAS")
                end
                if be:MDLisLive("f_devl24", local_5) == 1 then
                    be:sd("MODELCTRL", "f_devl24", local_5, "SQ_EXIT")
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
                else
                end
            end
            if local_3 >= 55.3 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM1")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            if local_3 >= 49.8 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM2")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            if local_3 >= 44.3 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM3")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            if local_3 >= 38.8 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM4")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            if local_3 >= 33.3 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM5")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            be:MDLsetSeq("SQ_FIRE21")
            for local_5 = 0, 1 do
                if be:MDLisLive("x_041fblst01a", local_5) == 1 then
                    be:sd("MODELCTRL", "x_041fblst01a", local_5, "SQ_ERAS")
                end
                if be:MDLisLive("f_devl24", local_5) == 1 then
                    be:sd("MODELCTRL", "f_devl24", local_5, "SQ_EXIT")
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
                else
                end
            end
            if local_3 >= 22 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM1")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            if local_3 >= 16.5 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM2")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            if local_3 >= 11 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM3")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            if local_3 >= 5.5 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM4")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            if local_3 > 0 then
                be:MDLsetSeq("SQ_LDMG")
                if be:MDLisLive("f_devl21", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DFORM5")
                else
                    be:sd("MODELCTRL", "f_devl21", 0, "SQ_DAMAGE")
                end
                if be:MDLisLive("f_devl23", 0) == 1 and g_arm == 1 then
                    be:sd("MODELCTRL", "f_devl23", 0, "SQ_DAMAGE")
                else
                end
            end
            for local_5 = 0, 1 do
                if be:MDLisLive("x_041fblst01a", local_5) == 1 then
                    be:sd("MODELCTRL", "x_041fblst01a", local_5, "SQ_ERAS")
                end
                if be:MDLisLive("f_devl24", local_5) == 1 then
                    be:sd("MODELCTRL", "f_devl24", local_5, "SQ_EXIT", 0)
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
            for local_7 = 0, 3 do
                if be:SYSisJoinPlayer(local_7) == 1 then
                    local_6 = local_6 + be:SYSctlPlayer("HP", "GETHP", local_7, 0)
                end
            end
            if local_6 ~= 0 then
                be:sd("MODELCTRL", nil, -1, "OFCTRL")
                if be:MDLisLive("i_bosshp05", 0) == 1 then
                    be:sd("MODELCTRL", "i_bosshp05", 0, "SQ_CLOSE")
                end
                be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
                be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "dead", local_0)
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
        if rank ~= 1 then
            if rank == 2 then
                if local_4 > 0 then
                    be:MDLsetSD("SETSTUN", "I<" .. local_4 .. ">")
                end
            end
        end
        if local_4 > 0 then
            be:MDLsetSD("SETSTUN", "I<" .. local_4 .. ">")
        end
        if rank ~= 3 then
            if local_4 > 0 then
                be:MDLsetSD("SETPOISON", "I<" .. local_4 .. ">/I<" .. local_5 .. ">")
            end
        end
        if be:MDLisLive("i_bosshp05", 0) == 1 then
            be:sd("METERCTRL", "bshp05", 0, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
        end
    end
end
