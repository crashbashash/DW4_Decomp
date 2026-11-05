be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
else
    if funcTameWazaHitCheck() == 0 then
        be:MDLaddHp(-50)
        if be:MDLgetHp() >= 50 then
            be:MDLsetSeq("SQ_SDMG")
            be:sd("MODELCTRL", "g_facteyez06", 0, "SQ_SDMG")
            be:sd("MODELCTRL", "g_facteyez06", 1, "SQ_SDMG")
        else
            be:MDLsetSeq("SQ_DEAD01")
            be:sd("MODELCTRL", "g_facteyez06", 0, "SQ_DEAD01")
            be:sd("MODELCTRL", "g_facteyez06", 1, "SQ_DEAD01")
            be:sd("CAMERA", nil, -1, "SHAKE", "15/F<0.2>/F<3.0>/F<60.0>,10")
            g_IFLG10 = 1
        end
    end
    be:MDLsetSeq("SQ_DEAD01")
end
