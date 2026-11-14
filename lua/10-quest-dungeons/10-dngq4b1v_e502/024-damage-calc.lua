be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
elseif funcTameWazaHitCheck() == 0 then
    be:MDLaddHp(-20)
else
    be:MDLaddHp(-be:MDLgetHp())
end
if be:MDLgetHp() > 0 then
    be:MDLsetSeq("SQ_SDMG")
else
    be:MDLsetSeq("SQ_DDMG")
end
