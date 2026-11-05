be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
else
    be:MDLaddHp(-100)
    be:MDLsetSeq("SQ_DDMG")
    if be:MDLgetRamNo() == 0 and be:MDLisLive("i_breakcur", 8) == 1 then
        be:sd("MODELCTRL", "i_breakcur", 8, "SQ_CLOSE")
    end
end
