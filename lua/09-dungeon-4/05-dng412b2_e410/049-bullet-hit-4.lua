if not g_HP0 then
    g_HP0 = 0
end
if not g_HP1 then
    g_HP1 = 0
end
if not g_HP2 then
    g_HP2 = 0
end
if not g_HP3 then
    g_HP3 = 0
end
if not g_HP4 then
    g_HP4 = 0
end
if not g_HP5 then
    g_HP5 = 0
end
if not g_HP6 then
    g_HP6 = 0
end
if not g_HP7 then
    g_HP7 = 0
end
if not g_shield0 then
    g_shield0 = 0
end
if not g_shield1 then
    g_shield1 = 0
end
if not g_shield2 then
    g_shield2 = 0
end
if not g_shield3 then
    g_shield3 = 0
end
if not g_shield4 then
    g_shield4 = 0
end
if not g_shield5 then
    g_shield5 = 0
end
if not g_shield6 then
    g_shield6 = 0
end
if not g_shield7 then
    g_shield7 = 0
end
if local_3 == 0 then
    local_1 = g_HP0
    local_2 = g_shield0
elseif local_3 == 1 then
    local_1 = g_HP1
    local_2 = g_shield1
elseif local_3 == 2 then
    local_1 = g_HP2
    local_2 = g_shield2
elseif local_3 == 3 then
    local_1 = g_HP3
    local_2 = g_shield3
elseif local_3 == 4 then
    local_1 = g_HP4
    local_2 = g_shield4
elseif local_3 == 5 then
    local_1 = g_HP5
    local_2 = g_shield5
elseif local_3 == 6 then
    local_1 = g_HP6
    local_2 = g_shield6
elseif local_3 == 7 then
    local_1 = g_HP7
    local_2 = g_shield7
end
if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetSeq("SQ_PUSHED")
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetSeq("SQ_GUARD")
elseif local_5 == 0 then
    if local_6 == 0 and local_6 > 0 then
        be:MDLsetSD("SETSLEEP", "I<" .. local_6 .. ">")
    end
    if local_6 == 0 and local_6 > 0 then
        be:MDLsetSD("SETBIND", "I<" .. local_6 .. ">")
    end
    if local_6 == 0 and local_6 > 0 then
        be:MDLsetSD("SETATTACKDOWN", "I<" .. local_6 .. ">/I<" .. local_7 .. ">/I<" .. local_8 .. ">/I<" .. local_9 .. ">/I<" .. local_10 .. ">")
    end
    if local_6 == 0 and local_6 > 0 then
        be:MDLsetSD("SETPOWERDOWN", "I<" .. local_6 .. ">/I<" .. local_7 .. ">/I<" .. local_8 .. ">")
    end
    if local_6 == 0 then
        be:MDLsetSeq("SQ_GUARD")
        be:BLTcalcSkillUp(0, 0)
    elseif local_6 < 0 then
        be:MDLsetDMGTurn(0)
        be:BLTcalcSkillUp(0, 0)
    else
        be:MDLsetDMGTurn(0)
        be:BLTcalcSkillUp(1, 0)
    end
else
    be:BLTcalcSkillUp(1, local_4)
    be:MDLaddHp(-local_5)
    be:MDLdspDamage(local_5)
    if local_6 < 3 and be:MDLisStatus(be:MDLgetInfoName(), be:MDLgetRamNo(), "BIND") == 1 then
        if be:MDLgetHp() <= local_7 then
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SCALL")
        else
            if local_2 == 1 then
                if local_0 == 0 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP0")
                elseif local_0 == 1 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP1")
                elseif local_0 == 2 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP2")
                elseif local_0 == 3 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP3")
                else
                end
            end
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SDMG")
        end
    end
    if local_6 == 0 then
        if be:MDLgetHp() <= local_7 then
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SCALL")
        else
            if local_2 == 1 then
                if local_0 == 0 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP0")
                elseif local_0 == 1 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP1")
                elseif local_0 == 2 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP2")
                elseif local_0 == 3 then
                    be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_SDMGP3")
                else
                end
            end
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SDMG")
        end
    end
    if local_6 == 1 then
        if be:MDLgetHp() <= local_7 then
            be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_MCALL")
        else
            if local_2 == 1 then
                if local_0 == 0 then
                    be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_MDMGP0")
                elseif local_0 == 1 then
                    be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_MDMGP1")
                elseif local_0 == 2 then
                    be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_MDMGP2")
                elseif local_0 == 3 then
                    be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_MDMGP3")
                else
                end
            end
            be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_MDMG")
        end
    end
    if local_6 == 2 then
        if be:MDLgetHp() <= local_7 then
            be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_LCALL")
        else
            if local_2 == 1 then
                if local_0 == 0 then
                    be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_LDMGP0")
                elseif local_0 == 1 then
                    be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_LDMGP1")
                elseif local_0 == 2 then
                    be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_LDMGP2")
                elseif local_0 == 3 then
                    be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                    be:MDLsetSeq("SQ_LDMGP3")
                else
                end
            end
            be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_LDMG")
        end
    end
    if local_6 == 3 then
        if local_2 == 1 then
            if local_0 == 0 then
                be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_DDMGP0")
            elseif local_0 == 1 then
                be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_DDMGP1")
            elseif local_0 == 2 then
                be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_DDMGP2")
            elseif local_0 == 3 then
                be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_DDMGP3")
            else
            end
        end
        be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_DDMG")
        be:MDLdspExp(be:BLTcalcEXPUp())
    end
    if local_6 ~= 1 then
        if local_6 == 2 then
            if local_8 > 0 then
                be:MDLsetSD("SETSTUN", "I<" .. local_8 .. ">")
            end
        end
    end
    if local_8 > 0 then
        be:MDLsetSD("SETSTUN", "I<" .. local_8 .. ">")
    end
    if local_6 ~= 3 then
        if local_8 > 0 then
            be:MDLsetSD("SETPOISON", "I<" .. local_8 .. ">/I<" .. local_9 .. ">")
        end
    end
end
