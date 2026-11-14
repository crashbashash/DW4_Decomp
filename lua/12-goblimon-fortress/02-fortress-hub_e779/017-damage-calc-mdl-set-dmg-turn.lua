be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
else
    be:MDLaddHp(-100)
    be:MDLsetSeq("SQ_DDMG")
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-46")
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-50")
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-53")
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-56")
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-61")
end
