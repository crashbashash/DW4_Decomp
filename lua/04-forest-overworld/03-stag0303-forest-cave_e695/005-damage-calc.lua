if be:MDLgetBulletKind() == 70119 then
    be:MDLsetDMGTurn(0)
    if be:SYSctlDeviceFolder("ISEQUIP", be:MDLgetRamNo(), "armor2", 42, 0, 0) == 0 then
        if local_2 ~= 0 then
            be:MDLaddHp(-local_2)
            be:MDLdspDamageP(local_2)
        else
            be:MDLaddHp(-1)
        end
        if be:MDLgetHp() == 0 then
            be:MDLsetSeq("SQ_DEAD")
        else
            if local_3 ~= "p_agumon" and local_3 ~= "p_vmon" and local_3 ~= "p_girumon" then
                if local_3 == "p_dorumon" then
                    be:sd("SOUND", nil, -1, "PLAY", "PC_DMG01")
                else
                    if local_3 ~= "p_metalgaru" then
                        if local_3 == "p_weregaru" then
                            be:sd("SOUND", nil, -1, "PLAY", "PC_DMG03")
                        else
                            be:sd("SOUND", nil, -1, "PLAY", "PC_DMG02")
                        end
                    end
                    be:sd("SOUND", nil, -1, "PLAY", "PC_DMG03")
                end
            end
            be:sd("SOUND", nil, -1, "PLAY", "PC_DMG01")
        end
        be:sd("METERCTRL", "hpmt", local_1, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
        be:sd("NUMBERCTRL", "hpnm", local_1, "SETVALUE", "I<" .. be:MDLgetHp() .. ">")
        be:sd("MODELCTRL", "i_stpnl02", local_1, "MOVETRANS", "V<" .. local_3[local_1 + 1] + -2 .. ",-158,0>/V<0,0,0>")
        be:sd("MODELCTRL", "i_stpnl02", local_1, "MOVETRANS", "V<" .. local_3[local_1 + 1] + -1 .. ",-162,0>/V<0,0,0>", 4)
        be:sd("MODELCTRL", "i_stpnl02", local_1, "MOVETRANS", "V<" .. local_3[local_1 + 1] + 1 .. ",-159,0>/V<0,0,0>", 8)
        be:sd("MODELCTRL", "i_stpnl02", local_1, "MOVETRANS", "V<" .. local_3[local_1 + 1] + 2 .. ",-161,0>/V<0,0,0>", 12)
        be:sd("MODELCTRL", "i_stpnl02", local_1, "MOVETRANS", "V<" .. local_3[local_1 + 1] + 0 .. ",-160,0>/V<0,0,0>", 16)
    end
elseif 80000 <= local_0 and local_0 < 90000 then
    be:MDLsetDMGTurn(0)
    be:BLTcalcSkillUp(local_1, 0)
else
    if be:MDLisSeqName("SQ_GUARD") ~= 1 then
        if be:BLPisHitCheck() == 0 then
            be:MDLsetSeq("SQ_GUARDR")
        elseif local_1 == 0 then
            if local_0 ~= 70002 then
                if local_0 == 70046 and local_2 == 0 and local_2 > 0 then
                    be:MDLsetSeq("SQ_STUN")
                    be:MDLsetSD("SETSTUN", "I<" .. local_2 .. ">")
                end
            end
            if local_2 == 0 and local_2 > 0 then
                be:MDLsetSeq("SQ_STUN")
                be:MDLsetSD("SETSTUN", "I<" .. local_2 .. ">")
            end
            if local_2 == 0 and local_2 > 0 then
                be:MDLsetSD("SETSLEEP", "I<" .. local_2 .. ">")
            end
            if local_2 == 0 and local_2 > 0 then
                be:MDLsetSD("SETBIND", "I<" .. local_2 .. ">")
            end
            if local_2 == 0 and local_2 > 0 then
                be:MDLsetSD("SETATTACKDOWN", "I<" .. local_2 .. ">/I<" .. local_3 .. ">/I<" .. local_4 .. ">/I<0>/I<0>")
            end
            if local_2 == 0 and local_2 > 0 then
                be:MDLsetSD("SETPOWERDOWN", "I<" .. local_2 .. ">/I<" .. local_3 .. ">/I<" .. local_4 .. ">")
            end
            if local_2 == 0 then
                be:MDLsetSeq("SQ_GUARDR")
            else
                be:MDLsetDMGTurn(0)
            end
        else
            be:MDLaddHp(-local_1)
            be:MDLdspDamageP(local_1)
            if local_2 == -1 then
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
            end
            if local_2 ~= 3 then
                if local_3 > 0 then
                    be:MDLsetSD("SETSTUN", "I<" .. local_3 .. ">")
                end
            end
            if local_2 ~= 3 then
                if local_3 > 0 then
                    be:MDLsetSD("SETBIND", "I<" .. local_3 .. ">")
                end
            end
            if local_2 ~= 3 then
                if local_3 > 0 then
                    be:MDLsetSD("SETPOISON", "I<" .. local_3 .. ">/I<" .. local_4 .. ">")
                end
            end
            be:sd("METERCTRL", "hpmt", be:MDLgetRamNo(), "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
            be:sd("NUMBERCTRL", "hpnm", be:MDLgetRamNo(), "SETVALUE", "I<" .. be:MDLgetHp() .. ">")
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_3[be:MDLgetRamNo() + 1] + -2 .. ",-158,0>/V<0,0,0>")
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_3[be:MDLgetRamNo() + 1] + -1 .. ",-162,0>/V<0,0,0>", 4)
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_3[be:MDLgetRamNo() + 1] + 1 .. ",-159,0>/V<0,0,0>", 8)
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_3[be:MDLgetRamNo() + 1] + 2 .. ",-161,0>/V<0,0,0>", 12)
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_3[be:MDLgetRamNo() + 1] + 0 .. ",-160,0>/V<0,0,0>", 16)
        end
    end
    be:MDLsetSeq("SQ_GUARDR")
end
