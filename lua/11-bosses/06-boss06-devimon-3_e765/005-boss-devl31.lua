be:MDLsetDMGTurn(0)
if not g_FIYCHACK then
    g_FIYCHACK = 0
end
if not g_FBSwitch then
    g_FBSwitch = 0
end
if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetDMGTurn(0)
    be:sd("PLAYER", be:SYSgetPlayerName(local_1), local_1, "SQ_GUARDR", 0)
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetDMGTurn(0)
    be:MDLsetSeq("SQ_GUARD")
elseif local_2 == 0 then
    if g_FIYCHACK == 0 and local_3 == 0 and local_3 > 0 then
        be:MDLsetSD("SETSLEEP", "I<" .. local_3 .. ">")
    end
    if g_FIYCHACK == 0 and local_3 == 0 and local_3 > 0 then
        be:MDLsetSD("SETBIND", "I<" .. local_3 .. ">")
        g_FBSwitch = 3
        be:MDLsetDMGTurn(0)
        be:MDLsetSeq("SQ_BIND")
    end
    if local_3 == 0 and local_3 > 0 then
        be:MDLsetSD("SETATTACKDOWN", "I<" .. local_3 .. ">/I<" .. local_4 .. ">/I<" .. local_5 .. ">/I<" .. local_6 .. ">/I<" .. local_7 .. ">")
    end
    if local_3 == 0 and local_3 > 0 then
        be:MDLsetSD("SETPOWERDOWN", "I<" .. local_3 .. ">/I<" .. local_4 .. ">/I<" .. local_5 .. ">")
    end
    if local_3 == 0 then
        be:MDLsetDMGTurn(0)
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
    if g_FIYCHACK == 0 then
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
            be:sd("MODELCTRL", "x_042fmagc01a", -1, "SQ_ERAS")
            be:sd("MODELCTRL", "f_devl31", -1, "SQ_ERAS")
            be:sd("ENEMY", be:MDLgetInfoName(), be:MDLgetRamNo(), "CLEARSTATUS")
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
                if be:MDLisLive("i_bosshp06", 0) == 1 then
                    be:sd("MODELCTRL", "i_bosshp06", 0, "SQ_CLOSE")
                end
                be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
                be:DMsetSD("SOUND", nil, -1, "PLAY", "d3FADE01")
                be:DMsetSD("SOUND", nil, -1, "ENVSTOP", "AM_BOS01")
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_DEVI3", 10)
                be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "dead", local_0)
                be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
                be:DMsetSD("PLAYER", nil, 0, "MOVETRANS", "V<-65,10,10>/V<0,90,0>", 0)
                be:DMsetSD("PLAYER", nil, 1, "MOVETRANS", "V<-65,10,-10>/V<0,90,0>", 0)
                be:DMsetSD("PLAYER", nil, 2, "MOVETRANS", "V<-60,10,30>/V<0,90,0>", 0)
                be:DMsetSD("PLAYER", nil, 3, "MOVETRANS", "V<-60,10,-30>/V<0,90,0>", 0)
                be:DMsetSD("MODELCTRL", "f_devl3", 0, "MOVETRANS", "V<60,10,0>/V<0,-90,0>", 1)
                be:DMsetSD("MODELCTRL", "f_devl3", 0, "MOVETRANS", "V<60,10,0>/V<0,-90,0>", 2)
                be:DMsetSD("SOUND", nil, -1, "VOLUMECTL2", "BT_DEVI3/F<1.0>/F<0.0>/F<240>")
                be:DMsetSD("SOUND", nil, -1, "BGMSTOP", "BT_DEVI3", 250)
                be:sd("SOUND", nil, -1, "PLAY", "BT_WIN04", 840)
                be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_WTOUT60", 880)
                be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_WTIN60", 1000)
                be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30", 1410)
                be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 1440)
                be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
                be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
                be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL")
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 20)
                be:DMrun()
                be:sd("PLAYER", nil, -1, "SQ_ENJOY", local_0 + 1480)
                be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<100,10,0>/V<0,-90,0>/SQ_ENTR", local_0 + 1520)
                be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON", local_0 + 1640)
                be:sd("GENERATER", nil, -1, "START", "GBOX-01", local_0 + 1580)
                be:FLGset(70, 1)
                if be:SYSgetDifficulty() > 0 then
                    be:FLGset(86, 1)
                    be:FLGset(610, 1)
                end
                be:FLGset(be:SYSgetDifficulty() + 406, 1)
            end
        end
        if local_3 ~= 1 then
            if local_3 == 2 then
                if local_4 > 0 then
                    be:MDLsetSD("SETSTUN", "I<" .. local_4 .. ">")
                end
            end
        end
        if local_4 > 0 then
            be:MDLsetSD("SETSTUN", "I<" .. local_4 .. ">")
        end
        if local_3 ~= 3 then
            if local_4 > 0 then
                be:MDLsetSD("SETPOISON", "I<" .. local_4 .. ">/I<" .. local_5 .. ">")
            end
        end
        if be:MDLisLive("i_bosshp06", 0) == 1 then
            be:sd("METERCTRL", "bshp06", 0, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
        end
    end
end
