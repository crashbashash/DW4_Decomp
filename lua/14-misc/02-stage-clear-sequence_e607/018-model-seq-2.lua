if 80000 <= local_0 and local_0 < 90000 then
    be:MDLsetDMGTurn(0)
    be:BLTcalcSkillUp(local_1, 0)
else
    if be:MDLisSeqName("SQ_GUARD") ~= 1 then
        if be:BLPisHitCheck() == 0 then
            be:MDLsetSeq("SQ_GUARDR")
        elseif local_1 == 0 then
            be:MDLsetSeq("SQ_GUARDR")
        else
            if local_2 == 0 then
                be:MDLsetSeq("SQ_SDMG")
            elseif local_2 == 1 then
                be:MDLsetSeq("SQ_SDMG")
            elseif local_2 == 2 then
                be:MDLsetSeq("SQ_SDMG")
            elseif local_2 == 3 then
                be:MDLsetSeq("SQ_SDMG")
            elseif local_2 == 4 then
                be:MDLsetSeq("SQ_MDMG")
            elseif local_2 == 5 then
                be:MDLsetSeq("SQ_MDMG")
            elseif local_2 == 6 then
                be:MDLsetSeq("SQ_LDMG")
            end
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_3[be:MDLgetRamNo() + 1] + -2 .. ",-158,0>/V<0,0,0>")
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_3[be:MDLgetRamNo() + 1] + -1 .. ",-162,0>/V<0,0,0>", 4)
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_3[be:MDLgetRamNo() + 1] + 1 .. ",-159,0>/V<0,0,0>", 8)
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_3[be:MDLgetRamNo() + 1] + 2 .. ",-161,0>/V<0,0,0>", 12)
            be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_3[be:MDLgetRamNo() + 1] .. ",-160,0>/V<0,0,0>", 16)
        end
    end
    be:MDLsetSeq("SQ_GUARDR")
end
