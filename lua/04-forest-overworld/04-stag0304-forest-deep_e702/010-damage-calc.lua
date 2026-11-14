be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
else
    be:MDLaddHp(-25)
    if be:MDLgetHp() >= 1 then
        be:MDLsetSeq("SQ_SDMG")
    else
        be:MDLsetSeq("SQ_DDMG")
    end
end
