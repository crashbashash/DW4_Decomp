if not g_magic then
    g_magic = 0
end
if not g_switch then
    g_switch = 0
end
if not g_sw0 then
    g_sw0 = 0
end
if not g_sw1 then
    g_sw1 = 0
end
if not g_sw2 then
    g_sw2 = 0
end
if not g_sw3 then
    g_sw3 = 0
end
if not g_sw4 then
    g_sw4 = 0
end
if not g_sw5 then
    g_sw5 = 0
end
if not g_sw6 then
    g_sw6 = 0
end
if not g_sw7 then
    g_sw7 = 0
end
if not g_sw8 then
    g_sw8 = 0
end
if not g_sw9 then
    g_sw9 = 0
end
if not g_sw10 then
    g_sw10 = 0
end
if not g_sw11 then
    g_sw11 = 0
end
if local_0 == 0 then
    if g_sw0 == 1 then
        g_sw0 = 2
        local_1 = 1
    elseif g_sw0 == 2 then
        local_1 = 2
    else
    end
end
if local_0 == 1 then
    if g_sw1 == 1 then
        g_sw1 = 2
        local_1 = 1
    elseif g_sw1 == 2 then
        local_1 = 2
    else
    end
end
if local_0 == 2 then
    if g_sw2 == 1 then
        g_sw2 = 2
        local_1 = 1
    elseif g_sw2 == 2 then
        local_1 = 2
    else
    end
end
if local_0 == 3 then
    if g_sw3 == 1 then
        g_sw3 = 2
        local_1 = 1
    elseif g_sw3 == 2 then
        local_1 = 2
    else
    end
end
if local_0 == 4 then
    if g_sw4 == 1 then
        g_sw4 = 2
        local_1 = 1
    elseif g_sw4 == 2 then
        local_1 = 2
    else
    end
end
if local_0 == 5 then
    if g_sw5 == 1 then
        g_sw5 = 2
        local_1 = 1
    elseif g_sw5 == 2 then
        local_1 = 2
    else
    end
end
if local_0 == 6 then
    if g_sw6 == 1 then
        g_sw6 = 2
        local_1 = 1
    elseif g_sw6 == 2 then
        local_1 = 2
    else
    end
end
if local_0 == 7 then
    if g_sw7 == 1 then
        g_sw7 = 2
        local_1 = 1
    elseif g_sw7 == 2 then
        local_1 = 2
    else
    end
end
if local_0 == 8 then
    if g_sw8 == 1 then
        g_sw8 = 2
        local_1 = 1
    elseif g_sw8 == 2 then
        local_1 = 2
    else
    end
end
if local_0 == 9 then
    if g_sw9 == 1 then
        g_sw9 = 2
        local_1 = 1
    elseif g_sw9 == 2 then
        local_1 = 2
    else
    end
end
if local_0 == 10 then
    if g_sw10 == 1 then
        g_sw10 = 2
        local_1 = 1
    elseif g_sw10 == 2 then
        local_1 = 2
    else
    end
end
if local_0 == 11 then
    if g_sw11 == 1 then
        g_sw11 = 2
        local_1 = 1
    elseif g_sw11 == 2 then
        local_1 = 2
    end
end
if be:MDLgetBulletKind() == 90123 then
    be:MDLsetSeq("SQ_SWON")
elseif be:MDLgetBulletKind() == 90026 then
    if local_1 == 1 and g_switch == 1 then
        be:MDLaddHp(be:MDLgetMHp() / 2)
        be:MDLsetSeq("SQ_RECV")
    else
        be:MDLsetSeq("SQ_NRECV")
    end
end
if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetSeq("SQ_PUSHED")
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetSeq("SQ_GUARD")
elseif local_3 == 0 then
    if local_4 == 0 and local_4 > 0 then
        be:MDLsetSD("SETSLEEP", "I<" .. local_4 .. ">")
    end
    if local_4 == 0 and local_4 > 0 then
        be:MDLsetSD("SETBIND", "I<" .. local_4 .. ">")
    end
    if local_4 == 0 and local_4 > 0 then
        be:MDLsetSD("SETATTACKDOWN", "I<" .. local_4 .. ">/I<" .. local_5 .. ">/I<" .. local_6 .. ">/I<" .. local_7 .. ">/I<" .. local_8 .. ">")
    end
    if local_4 == 0 and local_4 > 0 then
        be:MDLsetSD("SETPOWERDOWN", "I<" .. local_4 .. ">/I<" .. local_5 .. ">/I<" .. local_6 .. ">")
    end
    if local_4 == 0 then
        be:MDLsetSeq("SQ_GUARD")
        be:BLTcalcSkillUp(0, 0)
    elseif local_4 < 0 then
        be:MDLsetDMGTurn(0)
        be:BLTcalcSkillUp(0, 0)
    else
        be:MDLsetDMGTurn(0)
        be:BLTcalcSkillUp(1, 0)
    end
else
    be:BLTcalcSkillUp(1, local_2)
    be:MDLaddHp(-local_3)
    be:MDLdspDamage(local_3)
    if local_4 < 3 and be:MDLisStatus(be:MDLgetInfoName(), be:MDLgetRamNo(), "BIND") == 1 then
        if be:MDLgetHp() < be:MDLgetMHp() * 0.6 and be:MDLgetHp() + local_3 >= be:MDLgetMHp() * 0.6 then
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SMAGC")
        elseif be:MDLgetHp() < be:MDLgetMHp() * 0.3 and be:MDLgetHp() + local_3 >= be:MDLgetMHp() * 0.3 then
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SDMG")
        else
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SDMG")
        end
    end
    if local_4 < 3 and be:MDLgetHp() < be:MDLgetMHp() * 0.6 and be:MDLgetHp() + local_3 >= be:MDLgetMHp() * 0.6 then
        be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_LMAGC")
    elseif local_4 < 3 and be:MDLgetHp() < be:MDLgetMHp() * 0.3 and be:MDLgetHp() + local_3 >= be:MDLgetMHp() * 0.3 then
        be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_LDMG")
    elseif local_4 == 0 then
        be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_SDMG")
    elseif local_4 == 1 then
        be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_MDMG")
    elseif local_4 == 2 then
        be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_LDMG")
    elseif local_4 == 3 then
        be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_DDMG")
        be:MDLdspExp(be:BLTcalcEXPUp())
        if be:BLTgetShootRamNo() == 0 then
            be:COUNTERset(3, local_5)
            be:sd("NUMBERCTRL", "questnm0", 0, "SETVALUE", "I<" .. be:COUNTERget(3) .. ">")
        elseif be:BLTgetShootRamNo() == 1 then
            be:COUNTERset(4, local_5)
            be:sd("NUMBERCTRL", "questnm0", 1, "SETVALUE", "I<" .. be:COUNTERget(4) .. ">")
        elseif be:BLTgetShootRamNo() == 2 then
            be:COUNTERset(5, local_5)
            be:sd("NUMBERCTRL", "questnm0", 2, "SETVALUE", "I<" .. be:COUNTERget(5) .. ">")
        elseif be:BLTgetShootRamNo() == 3 then
            be:COUNTERset(6, local_5)
            be:sd("NUMBERCTRL", "questnm0", 3, "SETVALUE", "I<" .. be:COUNTERget(6) .. ">")
        end
        g_counter_total = be:COUNTERget(3) + be:COUNTERget(4) + be:COUNTERget(5) + be:COUNTERget(6)
        be:sd("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. g_counter_total .. ">")
    end
    if local_4 ~= 1 then
        if local_4 == 2 then
            if local_5 > 0 then
                be:MDLsetSD("SETSTUN", "I<" .. local_5 .. ">")
            end
        end
    end
    if local_5 > 0 then
        be:MDLsetSD("SETSTUN", "I<" .. local_5 .. ">")
    end
    if local_4 ~= 3 then
        if local_5 > 0 then
            be:MDLsetSD("SETPOISON", "I<" .. local_5 .. ">/I<" .. local_6 .. ">")
        end
    end
end
