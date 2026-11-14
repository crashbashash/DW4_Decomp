be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
elseif funcTameWazaHitCheck() == 0 then
    be:MDLaddHp(-50)
    if be:MDLgetHp() >= 50 then
        be:MDLsetSeq("SQ_SDMG")
    else
        be:MDLsetSeq("SQ_DDMG")
    end
else
    be:MDLsetSeq("SQ_DDMG")
end
