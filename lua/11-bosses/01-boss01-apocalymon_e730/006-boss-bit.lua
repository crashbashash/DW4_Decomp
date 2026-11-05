if be:MDLgetBulletName() == "PCBA" then
    be:sd("PLAYER", be:SYSgetPlayerName(local_0), local_0, "SQ_GUARDR", 0)
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetSeq("SQ_GUARD")
elseif local_1 == 0 then
    if local_2 == 0 and local_2 > 0 then
        be:MDLsetSD("SETSLEEP", "I<" .. local_2 .. ">")
    end
    if local_2 == 0 and local_2 > 0 then
        be:MDLsetSD("SETBIND", "I<" .. local_2 .. ">")
    end
    if local_2 == 0 and local_2 > 0 then
        be:MDLsetSD("SETATTACKDOWN", "I<" .. local_2 .. ">/I<" .. local_3 .. ">/I<" .. local_4 .. ">/I<" .. local_5 .. ">/I<" .. local_6 .. ">")
    end
    if local_2 == 0 and local_2 > 0 then
        be:MDLsetSD("SETPOWERDOWN", "I<" .. local_2 .. ">/I<" .. local_3 .. ">/I<" .. local_4 .. ">")
    end
    if local_2 == 0 then
        be:MDLsetSeq("SQ_GUARD")
        be:BLTcalcSkillUp(0, 0)
    elseif local_2 < 0 then
        be:MDLsetDMGTurn(0)
        be:BLTcalcSkillUp(0, 0)
    else
        be:MDLsetDMGTurn(0)
        be:BLTcalcSkillUp(1, 0)
    end
else
    be:BLTcalcSkillUp(1, local_0)
    be:MDLaddHp(-local_1)
    be:MDLdspDamage(local_1)
    if local_2 == 0 then
        be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_SDMG")
    elseif local_2 == 1 then
        be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_MDMG")
    elseif local_2 == 2 then
        be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_LDMG")
    elseif local_2 == 3 then
        be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_DDMG")
        be:BLTcalcEXPUp()
        for local_5 = 0, 3 do
            if be:SYSisJoinPlayer(local_5) == 1 then
                local_4 = local_4 + be:SYSctlPlayer("HP", "GETHP", local_5, 0)
            end
        end
        if local_4 ~= 0 then
            be:sd("MODELCTRL", nil, -1, "OFCTRL")
            if be:MDLisLive("i_bosshp01", 0) == 1 then
                be:sd("MODELCTRL", "i_bosshp01", 0, "SQ_CLOSE")
            end
            for local_5 = 0, 4 do
                if be:MDLisLive("g_b01cpole", local_5) == 1 then
                    be:sd("MODELCTRL", "g_b01cpole", local_5, "SQ_DDMG")
                end
            end
            if be:MDLisLive("f_bit", 0) == 1 then
                be:sd("MODELCTRL", "f_bit", 0, "SQ_EXIT")
            end
            for local_5 = 0, 4 do
                be:sd("MODELCTRL", "g_b01dmgf1", local_5, "SQ_WAIT")
                be:sd("MODELCTRL", "g_b01dmgf2", local_5, "SQ_SWOF")
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
    if local_2 ~= 1 then
        if local_2 == 2 then
            if local_3 > 0 then
                be:MDLsetSD("SETSTUN", "I<" .. local_3 .. ">")
            end
        end
    end
    if local_3 > 0 then
        be:MDLsetSD("SETSTUN", "I<" .. local_3 .. ">")
    end
    if local_2 ~= 3 then
        if local_3 > 0 then
            be:MDLsetSD("SETPOISON", "I<" .. local_3 .. ">/I<" .. local_4 .. ">")
        end
    end
    if be:MDLisLive("i_bosshp01", 0) == 1 then
        be:sd("METERCTRL", "bshp01", 0, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
    end
end
