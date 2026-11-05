be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
elseif be:BLTisPlayerBullet() == 0 then
else
    if funcTameWazaHitCheck() == 0 then
        be:MDLaddHp(-20)
        if be:MDLgetHp() >= 20 then
            be:MDLsetSeq("SQ_SDMG")
        else
            be:MDLsetSeq("SQ_DDMG")
        end
    end
    be:MDLsetSeq("SQ_DDMG")
end
