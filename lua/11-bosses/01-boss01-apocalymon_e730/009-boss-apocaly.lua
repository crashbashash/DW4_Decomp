be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
else
    be:MDLaddHp(-10)
    if be:MDLgetHp() >= 10 then
        be:MDLsetSeq("SQ_SDMG")
    else
        be:MDLsetSeq("SQ_DDMG")
        i = be:MDLgetRamNo() + 1
        rTbl = {???, ???, ???, ???, ???}
        rSet = {???, ???, ???, ???, ???}
        if be:MDLisLive("g_b01cpole", rTbl[i]) == 0 then
            be:sd("MODELCTRL", "g_b01dmgf1", rSet[i], "SQ_ATCK2")
        end
        lTbl = {???, ???, ???, ???, ???}
        lSet = {???, ???, ???, ???, ???}
        if be:MDLisLive("g_b01cpole", lTbl[i]) == 0 then
            be:sd("MODELCTRL", "g_b01dmgf1", lSet[i], "SQ_ATCK2")
        end
        all = 1
        for local_0 = 0, 4 do
            if be:MDLisLive("g_b01cpole", local_0) == 1 and local_0 ~= be:MDLgetRamNo() then
                all = 0
            end
        end
        if all == 1 then
            for local_0 = 0, 4 do
                be:sd("MODELCTRL", "g_b01dmgf1", local_0, "SQ_SWOF")
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
