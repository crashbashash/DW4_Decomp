if not g_DmgChk0 then
    g_DmgChk0 = 0
end
if not g_DmgChk1 then
    g_DmgChk1 = 0
end
if not g_DmgChk2 then
    g_DmgChk2 = 0
end
if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetSeq("SQ_PUSHED")
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetSeq("SQ_GUARD")
elseif local_2 == 0 then
    if local_3 == 0 and local_3 > 0 then
        be:MDLsetSD("SETSLEEP", "I<" .. local_3 .. ">")
    end
    if local_3 == 0 and local_3 > 0 then
        be:MDLsetSD("SETBIND", "I<" .. local_3 .. ">")
        be:MDLsetSeq("SQ_BIND")
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
        g_mecha4live = g_mecha4live + -1
        if g_mecha4live < 1 and g_UFOPos == -1 and g_act == 1 and g_devlDmgChk == 0 then
            be:sd("MODELCTRL", "f_devl1", 0, "SQ_SWARPIN")
        end
        if local_0 == 0 then
            g_DmgChk0 = 1
        elseif local_0 == 1 then
            g_DmgChk1 = 1
        elseif local_0 == 2 then
            g_DmgChk2 = 1
        end
        be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_DDMG")
        be:MDLdspExp(be:BLTcalcEXPUp())
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
end
