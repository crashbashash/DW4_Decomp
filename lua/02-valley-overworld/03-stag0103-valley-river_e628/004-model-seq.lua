if be:MDLisSeqName("SQ_GUARD") ~= 1 then
    if be:BLPisHitCheck() == 0 then
        be:MDLsetSeq("SQ_GUARDR")
    elseif local_0 == 0 then
        be:MDLsetSeq("SQ_GUARDR")
    else
        be:MDLsetSeq("SQ_SDMG")
        g_boathp = g_boathp - g_dmgnum
        if g_pCount == 1 then
            g_meta = g_meta - g_dmgnum * 0.5
        elseif g_pCount == 2 then
            g_meta = g_meta - g_dmgnum * 0.5
        elseif g_pCount == 3 then
            g_meta = g_meta - g_dmgnum * 0.75
        elseif g_pCount == 4 then
            g_meta = g_meta - g_dmgnum
        end
        be:sd("METERCTRL", "boathp", 0, "SETPERCENT", "F<" .. g_meta .. ">")
        if g_boathp == g_hpnum1 then
            be:sd("MODELCTRL", "g_boatz01", 0, "SQ_ADAM")
            be:sd("CAMERA", nil, -1, "SHAKE", "15732684/F<0.2>/F<3.0>/F<60.0>")
        elseif g_boathp == g_hpnum2 then
            be:sd("MODELCTRL", "g_boatz01", 0, "SQ_BDAM")
            be:sd("CAMERA", nil, -1, "SHAKE", "15732684/F<0.2>/F<3.0>/F<60.0>")
        elseif g_boathp == g_hpnum3 then
            be:sd("MODELCTRL", "g_boatz01", 0, "SQ_CDAM")
            be:sd("CAMERA", nil, -1, "SHAKE", "15732684/F<0.2>/F<3.0>/F<60.0>")
        elseif g_boathp == g_hpnum4 then
            be:sd("MODELCTRL", "g_boatz01", 0, "SQ_DDAM")
            be:sd("PLAYER", nil, -1, "OFCTRL")
            be:sd("ENEMY", nil, -1, "OFCTRL")
            be:sd("PLAYER", nil, -1, "SQ_DDMG", 5)
            be:sd("NDMWPANEL", nil, -1, "NOHEALING", "I<0>")
            be:sd("NDMWPANEL", nil, -1, "NOGATEDISK", "I<0>")
            be:sd("CAMERA", nil, -1, "SHAKE", "15732684/F<0.2>/F<3.0>/F<60.0>")
            be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_GAMEOVER", 120)
            be:sd("PLAYERPOINT", nil, -1, "SETGENERATEPOS", "I<4>", 300)
            be:sd("STAGECTL", nil, -1, "NEXTSTAGE", "stag0102", 300)
        end
        be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_1[be:MDLgetRamNo() + 1] + -2 .. ",-158,0>/V<0,0,0>")
        be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_1[be:MDLgetRamNo() + 1] + -1 .. ",-162,0>/V<0,0,0>", 4)
        be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_1[be:MDLgetRamNo() + 1] + 1 .. ",-159,0>/V<0,0,0>", 8)
        be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_1[be:MDLgetRamNo() + 1] + 2 .. ",-161,0>/V<0,0,0>", 12)
        be:sd("MODELCTRL", "i_stpnl02", be:MDLgetRamNo(), "MOVETRANS", "V<" .. local_1[be:MDLgetRamNo() + 1] .. ",-160,0>/V<0,0,0>", 16)
    end
end
be:MDLsetSeq("SQ_GUARDR")
