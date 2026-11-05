if be:MDLisSeqName("SQ_GUARD") ~= 1 then
    if be:BLPisHitCheck() == 0 then
        be:MDLsetSeq("SQ_GUARDR")
    elseif local_0 == 0 then
        if bKind ~= 70002 then
            if bKind == 70046 and local_1 == 0 and local_1 > 0 then
                be:MDLsetSeq("SQ_STUN")
                be:MDLsetSD("SETSTUN", "I<" .. local_1 .. ">")
            end
        end
        if local_1 == 0 and local_1 > 0 then
            be:MDLsetSeq("SQ_STUN")
            be:MDLsetSD("SETSTUN", "I<" .. local_1 .. ">")
        end
        if local_1 == 0 and local_1 > 0 then
            be:MDLsetSD("SETSLEEP", "I<" .. local_1 .. ">")
        end
        if local_1 == 0 and local_1 > 0 then
            be:MDLsetSD("SETBIND", "I<" .. local_1 .. ">")
        end
        if local_1 == 0 and local_1 > 0 then
            be:MDLsetSD("SETATTACKDOWN", "I<" .. local_1 .. ">/I<" .. local_2 .. ">/I<" .. local_3 .. ">/I<0>/I<0>")
        end
        if local_1 == 0 and local_1 > 0 then
            be:MDLsetSD("SETPOWERDOWN", "I<" .. local_1 .. ">/I<" .. local_2 .. ">/I<" .. local_3 .. ">")
        end
        if local_1 == 0 then
            be:MDLsetSeq("SQ_GUARDR")
        else
            be:MDLsetDMGTurn(0)
        end
    else
        be:MDLaddHp(-local_0)
        if local_1 == -1 then
        elseif local_1 == 0 then
            be:MDLsetSD("SETLABEL", "SQ_SDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_SDMG")
        elseif local_1 == 1 then
            be:MDLsetSD("SETLABEL", "SQ_MDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_MDMG")
        elseif local_1 == 2 then
            be:MDLsetSD("SETLABEL", "SQ_LDMG/" .. be:BLTgetAttributeStr())
            be:MDLsetSeq("SQ_LDMG")
        elseif local_1 == 3 and g_deadCheck == 4 then
            be:sd("ENEMY", nil, -1, "OFCTRL")
            be:sd("MODELCTRL", "r_trainz02", 0, "ONFREEZE")
            be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT60", 120)
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
            be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT60", "!=0")
            be:DMsetSD("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<5>", 1)
            be:DMsetSD("STAGECTL", nil, -1, "NEXTSTAGE", "stag0201", 1)
            be:DMrun()
        end
        if local_1 ~= 3 then
            if local_2 > 0 then
                be:MDLsetSD("SETSTUN", "I<" .. local_2 .. ">")
            end
        end
        if local_1 ~= 3 then
            if local_2 > 0 then
                be:MDLsetSD("SETBIND", "I<" .. local_2 .. ">")
            end
        end
        if local_1 ~= 3 then
            if local_2 > 0 then
                be:MDLsetSD("SETPOISON", "I<" .. local_2 .. ">/I<" .. local_3 .. ">")
            end
        end
        be:sd("METERCTRL", "hpmt", be:MDLgetRamNo(), "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
        be:sd("NUMBERCTRL", "hpnm", be:MDLgetRamNo(), "SETVALUE", "I<" .. be:MDLgetHp() .. ">")
        be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_2[be:MDLgetRamNo() + 1] + -2 .. ",-158,0>/V<0,0,0>")
        be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_2[be:MDLgetRamNo() + 1] + -1 .. ",-162,0>/V<0,0,0>", 4)
        be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_2[be:MDLgetRamNo() + 1] + 1 .. ",-159,0>/V<0,0,0>", 8)
        be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_2[be:MDLgetRamNo() + 1] + 2 .. ",-161,0>/V<0,0,0>", 12)
        be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_2[be:MDLgetRamNo() + 1] + 0 .. ",-160,0>/V<0,0,0>", 16)
    end
end
be:MDLsetSeq("SQ_GUARDR")
