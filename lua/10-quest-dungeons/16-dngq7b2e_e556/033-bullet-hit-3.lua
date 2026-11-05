if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetDMGTurn(0)
    be:sd("PLAYER", be:SYSgetPlayerName(local_0), local_0, "SQ_GUARDR", 0)
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetSeq("SQ_GUARD")
elseif local_1 == 0 then
    if local_2 == 0 and local_2 > 0 then
        be:MDLsetSD("SETSLEEP", "I<" .. local_2 .. ">")
    end
    if local_2 == 0 and local_2 > 0 then
        be:MDLsetSD("SETBIND", "I<" .. local_2 .. ">")
        be:MDLsetSeq("SQ_BIND")
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
    elseif local_2 < 3 and be:MDLgetHp() < be:MDLgetMHp() * 0.85 and be:MDLgetHp() + local_1 >= be:MDLgetMHp() * 0.85 then
        be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_LDMG")
    elseif local_2 < 3 and be:MDLgetHp() < be:MDLgetMHp() * 0.7 and be:MDLgetHp() + local_1 >= be:MDLgetMHp() * 0.7 then
        be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_LDMG")
    elseif local_2 < 3 and be:MDLgetHp() < be:MDLgetMHp() * 0.55 and be:MDLgetHp() + local_1 >= be:MDLgetMHp() * 0.55 then
        be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_LDMG")
    elseif local_2 < 3 and be:MDLgetHp() < be:MDLgetMHp() * 0.4 and be:MDLgetHp() + local_1 >= be:MDLgetMHp() * 0.4 then
        be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_LDMG")
    elseif local_2 < 3 and be:MDLgetHp() < be:MDLgetMHp() * 0.25 and be:MDLgetHp() + local_1 >= be:MDLgetMHp() * 0.25 then
        be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_LDMG")
    elseif local_2 < 3 and be:MDLgetHp() < be:MDLgetMHp() * 0.1 and be:MDLgetHp() + local_1 >= be:MDLgetMHp() * 0.1 then
        be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_LDMG")
    elseif local_2 == 0 then
        be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_SDMG")
    elseif local_2 == 1 then
        be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_MDMG")
    elseif local_2 == 2 then
        be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_LDMG")
    elseif local_2 == 3 and be:MDLisLive("i_bosshp14", 0) == 1 then
        be:sd("MODELCTRL", "i_bosshp14", 0, "SQ_CLOSE")
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
    if be:MDLisLive("i_bosshp14", 0) == 1 then
        be:sd("METERCTRL", "bshp14", 0, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
    end
end
