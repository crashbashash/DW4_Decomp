be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
elseif be:BLPgetAttackZokusei() == "fire" then
    be:MDLsetSeq("SQ_DDMG")
else
    be:MDLsetSeq("SQ_SDMG")
end
