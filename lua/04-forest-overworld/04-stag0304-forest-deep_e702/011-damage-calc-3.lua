be:MDLsetDMGTurn(0)
be:MDLaddHp(-20)
if funcTechWazaHitCheck() == 1 then
elseif be:MDLgetHp() >= 1 then
    be:MDLsetSeq("SQ_SDMG")
else
    be:MDLsetSeq("SQ_DDMG")
end
