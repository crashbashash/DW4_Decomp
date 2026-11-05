if local_0 ~= 70126 then
    if local_0 == 70127 and local_1 ~= 0 then
        return be:MDLgetBulletKind(), be:MDLgetRamNo()
    end
end
if local_1 ~= 0 then
    return be:MDLgetBulletKind(), be:MDLgetRamNo()
end
if local_0 ~= 70128 then
    if local_0 == 70129 and local_1 ~= 1 then
        return be:MDLgetBulletKind(), be:MDLgetRamNo()
    end
end
if local_1 ~= 1 then
    return be:MDLgetBulletKind(), be:MDLgetRamNo()
end
if local_0 ~= 70130 then
    if local_0 == 70131 and local_1 ~= 2 then
        return be:MDLgetBulletKind(), be:MDLgetRamNo()
    end
end
if local_1 ~= 2 then
    return be:MDLgetBulletKind(), be:MDLgetRamNo()
end
if local_0 ~= 70132 then
    if local_0 == 70133 and local_1 ~= 3 then
        return be:MDLgetBulletKind(), be:MDLgetRamNo()
    end
end
if local_1 ~= 3 then
    return be:MDLgetBulletKind(), be:MDLgetRamNo()
end
if 80000 <= local_0 and local_0 < 90000 then
    be:MDLsetDMGTurn(0)
    be:BLTcalcSkillUp(local_2, 0)
else
    if be:MDLisSeqName("SQ_GUARD") ~= 1 then
        if be:BLPisHitCheck() == 0 then
            be:MDLsetSeq("SQ_GUARDR")
        elseif local_2 == 0 then
            if local_0 ~= 70002 then
                if local_0 == 70046 and local_3 == 0 and local_3 > 0 then
                    be:MDLsetSeq("SQ_STUN")
                    be:MDLsetSD("SETSTUN", "I<" .. local_3 .. ">")
                end
            end
            if local_3 == 0 and local_3 > 0 then
                be:MDLsetSeq("SQ_STUN")
                be:MDLsetSD("SETSTUN", "I<" .. local_3 .. ">")
            end
            if local_3 == 0 and local_3 > 0 then
                be:MDLsetSD("SETSLEEP", "I<" .. local_3 .. ">")
            end
            if local_3 == 0 and local_3 > 0 then
                be:MDLsetSD("SETBIND", "I<" .. local_3 .. ">")
            end
            if local_3 == 0 and local_3 > 0 then
                be:MDLsetSD("SETATTACKDOWN", "I<" .. local_3 .. ">/I<" .. local_4 .. ">/I<" .. local_5 .. ">/I<0>/I<0>")
            end
            if local_3 == 0 and local_3 > 0 then
                be:MDLsetSD("SETPOWERDOWN", "I<" .. local_3 .. ">/I<" .. local_4 .. ">/I<" .. local_5 .. ">")
            end
            if local_3 == 0 then
                be:MDLsetSeq("SQ_GUARDR")
            else
                be:MDLsetDMGTurn(0)
            end
        else
            be:MDLaddHp(-local_2)
            be:MDLdspDamageP(local_2)
            if local_3 == -1 then
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
            end
            if local_3 ~= 3 then
                if local_4 > 0 then
                    be:MDLsetSD("SETSTUN", "I<" .. local_4 .. ">")
                end
            end
            if local_3 ~= 3 then
                if local_4 > 0 then
                    be:MDLsetSD("SETBIND", "I<" .. local_4 .. ">")
                end
            end
            if local_3 ~= 3 then
                if local_4 > 0 then
                    be:MDLsetSD("SETPOISON", "I<" .. local_4 .. ">/I<" .. local_5 .. ">/I<" .. local_6 .. ">")
                end
            end
            be:sd("METERCTRL", "hpmt", be:MDLgetRamNo(), "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
            be:sd("NUMBERCTRL", "hpnm", be:MDLgetRamNo(), "SETVALUE", "I<" .. be:MDLgetHp() .. ">")
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_4[be:MDLgetRamNo() + 1] + -2 .. ",-158,0>/V<0,0,0>")
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_4[be:MDLgetRamNo() + 1] + -1 .. ",-162,0>/V<0,0,0>", 4)
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_4[be:MDLgetRamNo() + 1] + 1 .. ",-159,0>/V<0,0,0>", 8)
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_4[be:MDLgetRamNo() + 1] + 2 .. ",-161,0>/V<0,0,0>", 12)
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_4[be:MDLgetRamNo() + 1] + 0 .. ",-160,0>/V<0,0,0>", 16)
        end
    end
    be:MDLsetSeq("SQ_GUARDR")
end
