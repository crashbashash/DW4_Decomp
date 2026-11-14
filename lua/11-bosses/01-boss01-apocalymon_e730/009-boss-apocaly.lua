be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
else
    be:MDLaddHp(-10)
    if be:MDLgetHp() >= 10 then
        be:MDLsetSeq("SQ_SDMG")
    else
        be:MDLsetSeq("SQ_DDMG")
        i = be:MDLgetRamNo() + 1
        rTbl = {4, 0, 1, 2, 3}
        rSet = {1, 0, 4, 3, 2}
        if be:MDLisLive("g_b01cpole", rTbl[i]) == 0 then
            be:sd("MODELCTRL", "g_b01dmgf1", rSet[i], "SQ_ATCK2")
        end
        lTbl = {1, 2, 3, 4, 0}
        lSet = {0, 4, 3, 2, 1}
        if be:MDLisLive("g_b01cpole", lTbl[i]) == 0 then
            be:sd("MODELCTRL", "g_b01dmgf1", lSet[i], "SQ_ATCK2")
        end
        all = 1
        for ramNo = 0, 4 do
            if be:MDLisLive("g_b01cpole", ramNo) == 1 and ramNo ~= be:MDLgetRamNo() then
                all = 0
            end
        end
        if all == 1 then
            for ramNo = 0, 4 do
                be:sd("MODELCTRL", "g_b01dmgf1", ramNo, "SQ_SWOF")
            end
            be:sd("MODELCTRL", "f_apocaly", 0, "SQ_PHASE2")
            if be:MDLisLive("f_bit", 0) == 0 then
                be:sd("MODELCTRL", "f_bit", 0, "GENERATE", "f_apocaly/I<0>/V<0,30,0>/V<0,90,0>/SQ_PHASE2")
            else
                be:sd("MODELCTRL", "f_bit", 0, "SQ_PHASE2")
            end
        end
    end
end
