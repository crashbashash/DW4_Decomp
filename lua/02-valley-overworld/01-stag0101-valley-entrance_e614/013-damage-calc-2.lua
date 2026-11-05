be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
else
    be:MDLaddHp(-50)
    if be:MDLgetHp() >= 50 then
        be:MDLsetSeq("SQ_SDMG")
    else
        be:MDLsetSeq("SQ_DDMG")
        if be:MDLgetRamNo() == 0 and be:MDLisLive("i_breakcur", 26) == 1 then
            be:sd("MODELCTRL", "i_breakcur", 26, "SQ_CLOSE")
        elseif be:MDLgetRamNo() == 1 and be:MDLisLive("i_breakcur", 27) == 1 then
            be:sd("MODELCTRL", "i_breakcur", 27, "SQ_CLOSE")
        end
    end
end
