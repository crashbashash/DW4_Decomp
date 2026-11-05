if not g_RNo0 then
    g_RNo0 = 0
elseif not g_RNo1 then
    g_RNo1 = 0
elseif not g_RNo2 then
    g_RNo2 = 0
elseif not g_RNo3 then
    g_RNo3 = 0
end
if g_RNo0 == 1 and local_1 == 0 then
    local_0 = 1
elseif g_RNo1 == 1 and local_1 == 1 then
    local_0 = 1
elseif g_RNo2 == 1 and local_1 == 2 then
    local_0 = 1
elseif g_RNo3 == 1 and local_1 == 3 then
    local_0 = 1
end
if local_0 == 1 then
    if be:MDLgetBulletKind() >= 40035 and be:MDLgetBulletKind() <= 40039 then
        be:MDLsetSeq("SQ_SWOF")
    else
    end
end
if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetSeq("SQ_PUSHED")
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetSeq("SQ_GUARD")
elseif local_3 == 0 then
    if local_0 == 0 and local_4 == 0 and local_4 > 0 then
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
        if be:MDLgetHp() < be:MDLgetMHp() / 2 and be:MDLgetHp() + local_3 >= be:MDLgetMHp() / 2 then
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SCNTDMG")
        else
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SDMG")
        end
    end
    if local_4 < 3 and be:MDLgetHp() < be:MDLgetMHp() / 2 and be:MDLgetHp() + local_3 >= be:MDLgetMHp() / 2 then
        if local_4 == 0 then
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SCNTDMG")
        elseif local_4 == 1 then
            be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_MCNTDMG")
        elseif local_4 == 2 then
            be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_LCNTDMG")
        else
        end
    end
    if local_4 == 0 then
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
    end
    if local_0 == 0 and local_4 == 2 then
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
