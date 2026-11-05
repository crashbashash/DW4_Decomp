if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetDMGTurn(0)
    be:sd("PLAYER", be:SYSgetPlayerName(local_3), local_3, "SQ_GUARDR", 0)
elseif be:BLTisHitCheck() == 0 then
    if g_act ~= 1 then
        if g_act == 2 then
            be:MDLsetSeq("SQ_GUARD")
        else
        end
    end
    be:MDLsetSeq("SQ_GUARD")
else
    be:MDLsetDMGTurn(0)
    if local_4 == 0 then
        if g_act ~= 1 then
            if g_act == 2 and local_5 == 0 and local_5 > 0 then
                be:MDLsetSD("SETSLEEP", "I<" .. local_5 .. ">")
            end
        end
        if local_5 == 0 and local_5 > 0 then
            be:MDLsetSD("SETSLEEP", "I<" .. local_5 .. ">")
        end
        if g_act == 2 and local_5 == 0 and local_5 > 0 then
            be:MDLsetSD("SETBIND", "I<" .. local_5 .. ">")
            be:MDLsetSeq("SQ_BIND")
        end
        if local_5 == 0 and local_5 > 0 then
            be:MDLsetSD("SETATTACKDOWN", "I<" .. local_5 .. ">/I<" .. local_6 .. ">/I<" .. local_7 .. ">/I<" .. local_8 .. ">/I<" .. local_9 .. ">")
        end
        if local_5 == 0 and local_5 > 0 then
            be:MDLsetSD("SETPOWERDOWN", "I<" .. local_5 .. ">/I<" .. local_6 .. ">/I<" .. local_7 .. ">")
        end
        if g_act ~= 1 then
            if g_act == 2 then
                if local_5 == 0 then
                    be:MDLsetSeq("SQ_GUARD")
                    be:BLTcalcSkillUp(0, 0)
                elseif local_5 < 0 then
                    be:MDLsetDMGTurn(0)
                    be:BLTcalcSkillUp(0, 0)
                else
                    be:MDLsetDMGTurn(0)
                    be:BLTcalcSkillUp(1, 0)
                end
            end
        end
        if local_5 == 0 then
            be:MDLsetSeq("SQ_GUARD")
            be:BLTcalcSkillUp(0, 0)
        elseif local_5 < 0 then
            be:MDLsetDMGTurn(0)
            be:BLTcalcSkillUp(0, 0)
        else
            be:MDLsetDMGTurn(0)
            be:BLTcalcSkillUp(1, 0)
        end
    else
        be:BLTcalcSkillUp(1, local_3)
        be:MDLaddHp(-local_4)
        be:MDLdspDamage(local_4)
        if local_5 < 3 and be:MDLisStatus(be:MDLgetInfoName(), be:MDLgetRamNo(), "BIND") == 1 then
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SDMG")
        elseif local_5 == 0 then
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SDMG")
        elseif local_5 == 1 then
            be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_MDMG")
        elseif local_5 == 2 then
            be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_LDMG")
        elseif local_5 == 3 then
            g_devlDmgChk = 1
            if g_act == 3 then
                g_act = 2
                be:sd("MODELCTRL", "f_devl1e", 0, "SQ_WAIT")
            end
            for local_8 = 0, 3 do
                if be:SYSisJoinPlayer(local_8) == 1 then
                    local_7 = local_7 + be:SYSctlPlayer("HP", "GETHP", local_8, 0)
                end
            end
            if local_7 == 0 then
                be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_LDMG")
                return 0, 0, 60, be:BLTisCritical(), be:BLTgetDamageValue(local_3), be:BLTgetDamageRank(be:MDLgetHp(), local_3), nil, 0
            end
            for local_8 = 0, 2 do
                if be:MDLisLive("f_devl1b", local_8) == 1 then
                    be:sd("ENEMY", be:MDLgetInfoName(), be:MDLgetRamNo(), "CLEARSTATUS")
                    be:MDLsetSeq("SQ_CHADMG")
                    be:sd("MODELCTRL", "f_devl1b", local_8, "SQ_CHADMG")
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
                for local_8 = 0, 2 do
                    if be:MDLisLive("e_mecha4bs", local_8) == 1 then
                        be:sd("MODELCTRL", "e_mecha4bs", local_8, "SQ_ERAS")
                    end
                end
                if be:MDLisLive("f_devl1c", 0) == 1 then
                    be:sd("MODELCTRL", "f_devl1c", 0, "SQ_ERAS")
                end
                be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "dead", local_2)
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
            if g_act == 2 and local_5 ~= 3 then
                if local_6 > 0 then
                    be:MDLsetSD("SETPOISON", "I<" .. local_6 .. ">/I<" .. local_7 .. ">")
                end
            end
        end
        if local_5 ~= 1 then
            if local_5 == 2 then
                if local_6 > 0 then
                    be:MDLsetSD("SETSTUN", "I<" .. local_6 .. ">")
                end
            end
        end
        if local_6 > 0 then
            be:MDLsetSD("SETSTUN", "I<" .. local_6 .. ">")
        end
        if local_5 ~= 3 then
            if local_6 > 0 then
                be:MDLsetSD("SETPOISON", "I<" .. local_6 .. ">/I<" .. local_7 .. ">")
            end
        end
        if be:MDLisLive("i_bosshp04", 0) == 1 then
            be:sd("METERCTRL", "bshp04", 0, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
        end
    end
end
