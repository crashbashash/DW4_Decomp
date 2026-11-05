be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
elseif be:FLGisOn(489) == 0 and be:MDLgetRamNo(be:FLGisOn(), be, 487) == 0 then
    be:MDLaddHp(-35)
    if be:MDLgetHp() == 65 then
        be:MDLsetSeq("SQ_SDMG01")
    elseif be:MDLgetHp() == 30 then
        be:MDLsetSeq("SQ_MDMG01")
    elseif be:MDLgetHp() <= 0 and be:FLGisOn(481) == 1 and be:FLGisOn(482) == 1 and be:FLGisOn(483) == 1 and be:FLGisOn(484) == 1 and be:FLGisOn(485) == 1 and be:FLGisOn(486) == 1 and be:FLGisOn(487) == 1 and be:FLGisOn(488) == 1 and be:FLGisOn(489) == 0 then
        be:sd("MODELCTRL", "g_annihilativebomz06", 1, "SQ_SWON", 30)
        be:sd("MODELCTRL", "g_annihilativebomz06", 0, "SQ_SWON", 30)
        be:sd("MODELCTRL", "g_annihilativebomz06", 1, "SQ_DEAD", 150)
        be:sd("MODELCTRL", "g_annihilativebomz06", 0, "SQ_DEAD", 150)
        be:sd("MODELCTRL", "g_dumperz06", 0, "SQ_DDMG", 150)
        be:FLGset(489, 1)
    else
    end
end
