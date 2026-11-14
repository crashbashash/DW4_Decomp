be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
else
    be:MDLaddHp(-100)
    be:MDLsetSeq("SQ_DDMG")
    be:sd("MODELCTRL", "g_breakinggatez05", 1, "SQ_SWON")
    be:sd("HITLANDMODEL", "hitbreakinggatez051", 0, "OFFHIT")
    be:sd("GENERATER", nil, -1, "STOP", "GENE-23")
    be:sd("GENERATER", nil, -1, "START", "GENE-00")
    be:sd("GENERATER", nil, -1, "START", "GENE-19")
end
