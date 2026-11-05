be:MDLsetDMGTurn(0)
if not g_Rocksh0 then
    g_Rocksh0 = 0
end
if not g_Rocksh1 then
    g_Rocksh1 = 0
end
if not g_Rocksh2 then
    g_Rocksh2 = 0
end
if not g_Rocksh3 then
    g_Rocksh3 = 0
end
if g_Rocksh0 == 1 and local_1 == 0 then
    local_2 = 1
elseif g_Rocksh1 == 1 and local_1 == 1 then
    local_2 = 1
elseif g_Rocksh2 == 1 and local_1 == 2 then
    local_2 = 1
elseif g_Rocksh3 == 1 and local_1 == 3 then
    local_2 = 1
end
if local_3 == 0 and local_2 == 1 and be:MDLgetBulletBoxNo() == 0 then
    if be:MDLgetBulletKind() >= 40040 and be:MDLgetBulletKind() <= 40090 then
        be:MDLsetSeq("SQ_WAIT")
        local_3 = 1
        be:BLTcalcSkillUp(0, 0)
    elseif be:MDLgetBulletName() == "PCBA" then
        be:MDLsetDMGTurn(0)
        be:sd("PLAYER", be:SYSgetPlayerName(local_4), local_4, "SQ_GUARDR", 0)
        local_3 = 1
    end
end
if local_3 == 0 and local_2 == 1 and be:MDLgetBulletBoxNo(be:MDLgetBulletBoxNo(), be) == 2 then
    if be:MDLgetBulletKind() < 40035 then
        if local_0 == 0 then
            be:MDLsetSeq("SQ_DMGP0")
            local_3 = 1
        elseif local_0 == 1 then
            be:MDLsetSeq("SQ_DMGP1")
            local_3 = 1
        elseif local_0 == 2 then
            be:MDLsetSeq("SQ_DMGP2")
            local_3 = 1
        elseif local_0 == 3 then
            be:MDLsetSeq("SQ_DMGP3")
            local_3 = 1
        else
        end
    end
    if be:MDLgetBulletKind() >= 40040 and be:MDLgetBulletKind() <= 40090 then
        be:MDLsetSeq("SQ_WAIT")
        local_3 = 1
        be:BLTcalcSkillUp(0, 0)
    end
end
if local_3 == 0 then
    if be:MDLgetBulletName() == "PCBA" then
        be:MDLsetDMGTurn(0)
        be:sd("PLAYER", be:SYSgetPlayerName(local_4), local_4, "SQ_GUARDR", 0)
        local_3 = 1
    elseif be:BLTisHitCheck() == 0 then
        be:MDLsetSeq("SQ_GUARD")
        local_3 = 1
    elseif local_5 == 0 then
        if local_6 == 0 and local_6 > 0 then
            if local_2 ~= 1 then
                be:MDLsetSD("SETSLEEP", "I<" .. local_6 .. ">")
            else
                local_6 = -1
            end
        end
        if local_6 == 0 and local_6 > 0 then
            if local_2 ~= 1 then
                be:MDLsetSD("SETBIND", "I<" .. local_6 .. ">")
            else
                local_6 = -1
            end
        end
        if local_6 == 0 and local_6 > 0 then
            if local_2 ~= 1 then
                be:MDLsetSD("SETATTACKDOWN", "I<" .. local_6 .. ">/I<" .. local_7 .. ">/I<" .. local_8 .. ">/I<" .. local_9 .. ">/I<" .. local_10 .. ">")
            else
                local_6 = -1
            end
        end
        if local_6 == 0 and local_6 > 0 then
            if local_2 ~= 1 then
                be:MDLsetSD("SETPOWERDOWN", "I<" .. local_6 .. ">/I<" .. local_7 .. ">/I<" .. local_8 .. ">")
            else
                local_6 = -1
            end
        end
        if local_6 == 0 then
            if local_2 ~= 1 then
                be:MDLsetSeq("SQ_GUARD")
                be:BLTcalcSkillUp(0, 0)
            elseif local_2 == 1 and be:MDLgetBulletBoxNo() == 0 then
                be:MDLsetDMGTurn(0)
                be:MDLsetSeq("SQ_DMGOF")
                local_3 = 1
            else
            end
        end
        if local_6 < 0 then
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
            if local_2 == 1 and be:MDLgetBulletBoxNo() == 0 then
                be:MDLsetSeq("SQ_DMGOF")
                local_3 = 1
            elseif local_2 == 1 and be:MDLgetBulletKind() >= 40035 and be:MDLgetBulletKind() <= 40039 then
                be:MDLsetSeq("SQ_DMGOF")
                local_3 = 1
            else
                be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_SDMG")
                local_3 = 1
            end
        end
        if local_6 == 0 then
            if local_2 == 1 and be:MDLgetBulletBoxNo() == 0 then
                be:MDLsetSeq("SQ_DMGOF")
                local_3 = 1
            elseif local_2 == 1 and be:MDLgetBulletKind() >= 40035 and be:MDLgetBulletKind() <= 40039 then
                be:MDLsetSeq("SQ_DMGOF")
                local_3 = 1
            else
                be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_SDMG")
                local_3 = 1
            end
        end
        if local_6 == 1 then
            if local_2 == 1 and be:MDLgetBulletBoxNo() == 0 then
                be:MDLsetSeq("SQ_DMGOF")
                local_3 = 1
            elseif local_2 == 1 and be:MDLgetBulletKind() >= 40035 and be:MDLgetBulletKind() <= 40039 then
                be:MDLsetSeq("SQ_DMGOF")
                local_3 = 1
            else
                be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_MDMG")
                local_3 = 1
            end
        end
        if local_6 == 2 then
            if local_2 == 1 and be:MDLgetBulletBoxNo() == 0 then
                be:MDLsetSeq("SQ_DMGOF")
                local_3 = 1
            elseif local_2 == 1 and be:MDLgetBulletKind() >= 40035 and be:MDLgetBulletKind() <= 40039 then
                be:MDLsetSeq("SQ_DMGOF")
                local_3 = 1
            else
                be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_LDMG")
                local_3 = 1
            end
        end
        if local_6 == 3 then
            if local_2 == 1 then
                be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_DDMG")
                local_3 = 1
            else
                be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
                be:MDLsetSeq("SQ_DDMG")
                local_3 = 1
            end
            be:MDLdspExp(be:BLTcalcEXPUp())
            local_3 = 1
            if be:MDLisLive("i_bosshp16", 0) == 1 then
                be:sd("MODELCTRL", "i_bosshp16", 0, "SQ_CLOSE")
            end
        end
        if local_2 == 0 and local_6 == 2 then
            if local_7 > 0 then
                be:MDLsetSD("SETSTUN", "I<" .. local_7 .. ">")
            end
        end
        if local_2 == 0 and local_6 ~= 3 then
            if local_7 > 0 then
                be:MDLsetSD("SETPOISON", "I<" .. local_7 .. ">/I<" .. local_8 .. ">")
            end
        end
        if local_6(1, be:MDLisLive(), be, "i_bosshp16", 0) == 1 then
            be:sd("METERCTRL", "bshp16", 0, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
        end
    end
end
