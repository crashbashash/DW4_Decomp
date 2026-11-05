if not g_magic then
    g_magic = 0
end
if not g_switch then
    g_switch = 0
end
if be:MDLgetBulletName() == "ENSP" then
    be:MDLsetDMGTurn(0)
elseif be:MDLgetBulletName() == "PCBA" then
    be:MDLsetSeq("SQ_PUSHED")
else
    if be:BLTisHitCheck() ~= 0 then
        if be:MDLgetBulletBoxNo() == 0 then
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
            if local_2 < 3 and be:MDLisStatus(be:MDLgetInfoName(), be:MDLgetRamNo(), "BIND") == 1 then
                be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_SDMG")
            elseif local_2 == 0 then
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
                be:MDLdspExp(be:BLTcalcEXPUp())
                if be:BLTgetShootRamNo() == 0 then
                    be:COUNTERset(3, local_3)
                    be:sd("NUMBERCTRL", "questnm0", 0, "SETVALUE", "I<" .. be:COUNTERget(3) .. ">")
                elseif be:BLTgetShootRamNo() == 1 then
                    be:COUNTERset(4, local_3)
                    be:sd("NUMBERCTRL", "questnm0", 1, "SETVALUE", "I<" .. be:COUNTERget(4) .. ">")
                elseif be:BLTgetShootRamNo() == 2 then
                    be:COUNTERset(5, local_3)
                    be:sd("NUMBERCTRL", "questnm0", 2, "SETVALUE", "I<" .. be:COUNTERget(5) .. ">")
                elseif be:BLTgetShootRamNo() == 3 then
                    be:COUNTERset(6, local_3)
                    be:sd("NUMBERCTRL", "questnm0", 3, "SETVALUE", "I<" .. be:COUNTERget(6) .. ">")
                end
                g_counter_total = be:COUNTERget(3) + be:COUNTERget(4) + be:COUNTERget(5) + be:COUNTERget(6)
                be:sd("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. g_counter_total .. ">")
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
        end
    end
    be:MDLsetSeq("SQ_GUARD")
end
