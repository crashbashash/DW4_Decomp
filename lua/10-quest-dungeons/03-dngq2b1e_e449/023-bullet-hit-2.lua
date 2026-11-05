if not g_lifeaid0 then
    g_lifeaid0 = 0
end
if not g_lifeaid1 then
    g_lifeaid1 = 0
end
if not g_lifeaid2 then
    g_lifeaid2 = 0
end
if not g_lifeaid3 then
    g_lifeaid3 = 0
end
if be:MDLgetRamNo() == 0 and g_lifeaid0 ~= 0 then
    local_0 = 1
elseif be:MDLgetRamNo() == 1 and g_lifeaid1 ~= 0 then
    local_0 = 1
elseif be:MDLgetRamNo() == 2 and g_lifeaid2 ~= 0 then
    local_0 = 1
elseif be:MDLgetRamNo() == 3 and g_lifeaid3 ~= 0 then
    local_0 = 1
end
if be:MDLgetBulletName() == "ENSP" then
    be:MDLsetDMGTurn(0)
elseif be:MDLgetBulletName() == "PCBA" then
    be:MDLsetSeq("SQ_PUSHED")
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetSeq("SQ_GUARDR")
elseif local_2 == 0 then
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
    be:MDLaddHp(-local_2)
    be:MDLdspDamage(local_2)
    if local_3 < 3 and be:MDLisStatus(be:MDLgetInfoName(), be:MDLgetRamNo(), "BIND") == 1 then
        be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_SDMG")
    elseif local_3 < 3 and be:MDLgetHp() < be:MDLgetMHp() / 2 and local_0 == 0 then
        be:MDLsetSeq("SQ_SWON")
        be:MDLsetSeq("SQ_LDMG")
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
        be:MDLdspExp(be:BLTcalcEXPUp())
        if be:BLTgetShootRamNo() == 0 then
            be:COUNTERset(3, local_4)
            be:sd("NUMBERCTRL", "questnm0", 0, "SETVALUE", "I<" .. be:COUNTERget(3) .. ">")
        elseif be:BLTgetShootRamNo() == 1 then
            be:COUNTERset(4, local_4)
            be:sd("NUMBERCTRL", "questnm0", 1, "SETVALUE", "I<" .. be:COUNTERget(4) .. ">")
        elseif be:BLTgetShootRamNo() == 2 then
            be:COUNTERset(5, local_4)
            be:sd("NUMBERCTRL", "questnm0", 2, "SETVALUE", "I<" .. be:COUNTERget(5) .. ">")
        elseif be:BLTgetShootRamNo() == 3 then
            be:COUNTERset(6, local_4)
            be:sd("NUMBERCTRL", "questnm0", 3, "SETVALUE", "I<" .. be:COUNTERget(6) .. ">")
        end
        g_counter_total = be:COUNTERget(3) + be:COUNTERget(4) + be:COUNTERget(5) + be:COUNTERget(6)
        be:sd("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. g_counter_total .. ">")
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
