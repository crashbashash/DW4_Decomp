if not g_mode then
    g_mode = 0
end
if not g_Ground then
    g_Ground = 0
end
if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetDMGTurn(0)
    be:sd("PLAYER", be:SYSgetPlayerName(local_1), local_1, "SQ_GUARDR", 0)
elseif be:BLTisHitCheck() == 0 then
    if g_Ground == 1 then
        be:MDLsetSeq("SQ_GUARD")
    else
    end
end
be:MDLsetDMGTurn(0)
if local_2 == 0 then
    if g_Ground == 1 and local_3 == 0 and local_3 > 0 then
        be:MDLsetSD("SETSLEEP", "I<" .. local_3 .. ">")
    end
    if g_Ground == 1 and local_3 == 0 and local_3 > 0 then
        be:MDLsetSD("SETBIND", "I<" .. local_3 .. ">")
    end
    if local_3 == 0 and local_3 > 0 then
        be:MDLsetSD("SETATTACKDOWN", "I<" .. local_3 .. ">/I<" .. local_4 .. ">/I<" .. local_5 .. ">/I<" .. local_6 .. ">/I<" .. local_7 .. ">")
    end
    if local_3 == 0 and local_3 > 0 then
        be:MDLsetSD("SETPOWERDOWN", "I<" .. local_3 .. ">/I<" .. local_4 .. ">/I<" .. local_5 .. ">")
    end
    if g_Ground == 1 then
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
    be:BLTcalcSkillUp(1, local_1)
    if g_Ground == 1 then
        be:MDLaddHp(-local_2)
        be:MDLdspDamage(local_2)
        if local_3 < 3 and be:MDLisStatus(be:MDLgetInfoName(), be:MDLgetRamNo(), "BIND") == 1 then
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SDMG")
        elseif local_3 == 0 then
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SDMG")
        elseif local_3 == 1 then
            be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_MDMG")
        elseif local_3 == 2 then
            be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_LDMG")
        elseif local_3 == 3 then
            be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_DDMG")
            be:BLTcalcEXPUp()
            for local_6 = 0, 3 do
                if be:SYSisJoinPlayer(local_6) == 1 then
                    local_5 = local_5 + be:SYSctlPlayer("HP", "GETHP", local_6, 0)
                end
            end
            if local_5 ~= 0 then
                be:sd("MODELCTRL", nil, -1, "OFCTRL")
                if be:MDLisLive("i_bosshp03", 0) == 1 then
                    be:sd("MODELCTRL", "i_bosshp03", 0, "SQ_CLOSE")
                end
                be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
                be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "dead", local_0)
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
                be:sd("SOUND", NULL, -1, "PLAY", "BT_WIN02", local_0 + 120)
                be:sd("PLAYER", nil, -1, "SQ_ENJOY", local_0 + 210)
                be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-23.75,10,-23.75>/V<0,45,0>/SQ_ENTR", local_0 + 330)
                be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON", local_0 + 360)
                be:sd("GENERATER", nil, -1, "START", "GBOX-01", local_0 + 330)
                be:FLGset(69, 1)
                if be:SYSgetDifficulty() > 0 then
                    be:FLGset(607, 1)
                end
                be:COUNTERset(2, 0)
            end
        end
    end
end
if g_Ground == 1 and rank == 2 then
    if local_3 > 0 then
        be:MDLsetSD("SETSTUN", "I<" .. local_3 .. ">")
    end
end
if g_Ground == 1 and rank ~= 3 then
    if local_3 > 0 then
        be:MDLsetSD("SETPOISON", "I<" .. local_3 .. ">/I<" .. local_4 .. ">")
    end
end
if rank(1, be:MDLisLive(), be, "i_bosshp03", 0) == 1 then
    be:sd("METERCTRL", "bshp03", 0, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
end
