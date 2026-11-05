be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 0 and be:MDLgetBulletName() ~= "ENAT" then
    if be:BLPgetAttackZokusei() == "thunder" then
        be:MDLsetSeq("SQ_DDMG")
    else
        be:MDLsetSeq("SQ_SDMG")
    end
end
