if not g_run0 then
    g_run0 = 0
end
if not g_run1 then
    g_run1 = 0
end
if not g_run2 then
    g_run2 = 0
end
if g_run0 == 1 and local_0 == 0 then
    local_1 = 1
end
if g_run1 == 1 and local_0 == 1 then
    local_1 = 1
end
if g_run2 == 1 and local_0 == 2 then
    local_1 = 1
end
if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetDMGTurn(0)
    be:sd("PLAYER", be:SYSgetPlayerName(local_2), local_2, "SQ_GUARDR", 0)
elseif be:BLTisHitCheck() == 0 then
    if local_1 == 0 then
        be:MDLsetSeq("SQ_GUARD")
    else
    end
end
be:MDLsetDMGTurn(0)
if local_3 == 0 then
    if local_1 == 0 and local_4 == 0 and local_4 > 0 then
        be:MDLsetSD("SETSLEEP", "I<" .. local_4 .. ">")
    end
    if local_1 == 0 and local_4 == 0 and local_4 > 0 then
        be:MDLsetSD("SETBIND", "I<" .. local_4 .. ">")
        be:MDLsetSeq("SQ_BIND")
    end
    if local_4 == 0 and local_4 > 0 then
        be:MDLsetSD("SETATTACKDOWN", "I<" .. local_4 .. ">/I<" .. local_5 .. ">/I<" .. local_6 .. ">/I<" .. local_7 .. ">/I<" .. local_8 .. ">")
    end
    if local_4 == 0 and local_4 > 0 then
        be:MDLsetSD("SETPOWERDOWN", "I<" .. local_4 .. ">/I<" .. local_5 .. ">/I<" .. local_6 .. ">")
    end
    if local_1 == 0 then
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
    end
else
    be:BLTcalcSkillUp(1, local_2)
    be:MDLaddHp(-local_3)
    be:MDLdspDamage(local_3)
    if local_4 < 3 and be:MDLisStatus(be:MDLgetInfoName(), be:MDLgetRamNo(), "BIND") == 1 then
        be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_SDMG")
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
        g_devl1blive = g_devl1blive + -1
        be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_DDMG")
        be:BLTcalcEXPUp()
    end
    if local_1 == 0 and local_4 == 2 then
        if local_5 > 0 then
            be:MDLsetSD("SETSTUN", "I<" .. local_5 .. ">")
        end
    end
    if local_4 ~= 3 then
        if local_5 > 0 then
            be:MDLsetSD("SETPOISON", "I<" .. local_5 .. ">/I<" .. local_6 .. ">")
        end
    end
end
