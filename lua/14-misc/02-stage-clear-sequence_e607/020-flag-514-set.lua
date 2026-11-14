be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
else
    be:MDLaddHp(-100)
    be:MDLsetSeq("SQ_DDMG")
    if be:FLGisOn(514) == 0 then
        be:sd("MODELCTRL", "g_tcounter00", 0, "GENERATE")
        be:FLGset(514, 1)
    end
end
