be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
else
    be:MDLaddHp(-100)
    be:MDLsetSeq("SQ_DDMG")
end
