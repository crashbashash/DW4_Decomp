local bulletKind = be:MDLgetBulletKind()
if be:MDLgetBulletKind() == 70119 then
    be:MDLsetDMGTurn(0)
    local ramNo = be:MDLgetRamNo()
    if be:SYSctlDeviceFolder("ISEQUIP", be:MDLgetRamNo(), "armor2", 42, 0, 0) == 0 then
        local damageValue = be:BLPgetDamageValue()
        if damageValue ~= 0 then
            be:MDLaddHp(-damageValue)
            be:MDLdspDamageP(damageValue)
        else
            be:MDLaddHp(-1)
        end
        if be:MDLgetHp() == 0 then
            be:MDLsetSeq("SQ_DEAD")
        else
            local playerName = be:SYSgetPlayerName(ramNo)
            if playerName ~= "p_agumon" and playerName ~= "p_vmon" and playerName ~= "p_girumon" then
                if playerName == "p_dorumon" then
                end
            end
            be:sd("SOUND", nil, -1, "PLAY", "PC_DMG01")
        end
        be:sd("METERCTRL", "hpmt", ramNo, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
        be:sd("NUMBERCTRL", "hpnm", ramNo, "SETVALUE", "I<" .. be:MDLgetHp() .. ">")
        local list = {-260, -110, 40, 190}
        be:sd("MODELCTRL", "i_stpnl02", ramNo, "MOVETRANS", "V<" .. list[ramNo + 1] + -2 .. ",-158,0>/V<0,0,0>")
        be:sd("MODELCTRL", "i_stpnl02", ramNo, "MOVETRANS", "V<" .. list[ramNo + 1] + -1 .. ",-162,0>/V<0,0,0>", 4)
        be:sd("MODELCTRL", "i_stpnl02", ramNo, "MOVETRANS", "V<" .. list[ramNo + 1] + 1 .. ",-159,0>/V<0,0,0>", 8)
        be:sd("MODELCTRL", "i_stpnl02", ramNo, "MOVETRANS", "V<" .. list[ramNo + 1] + 2 .. ",-161,0>/V<0,0,0>", 12)
        be:sd("MODELCTRL", "i_stpnl02", ramNo, "MOVETRANS", "V<" .. list[ramNo + 1] + 0 .. ",-160,0>/V<0,0,0>", 16)
    end
elseif 80000 <= bulletKind and bulletKind < 90000 then
    be:MDLsetDMGTurn(0)
    local effectMagic = be:BLPcalcKoukaMagic()
    be:BLTcalcSkillUp(effectMagic, 0)
else
    if be:MDLisSeqName("SQ_GUARD") ~= 1 then
        if be:BLPisHitCheck() == 0 then
        end
    end
    be:MDLsetSeq("SQ_GUARDR")
end
