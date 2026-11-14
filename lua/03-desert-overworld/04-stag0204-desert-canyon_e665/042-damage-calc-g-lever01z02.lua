be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
elseif funcTameWazaHitCheck() == 0 then
    be:MDLaddHp(-50)
    if be:MDLgetHp() >= 50 then
        be:MDLsetSeq("SQ_SDMG")
    else
        be:MDLsetSeq("SQ_DDMG")
        be:sd("HITLANDMODEL", "hitwall01z02", 0, "OFFHIT")
        be:sd("MODELCTRL", "g_lever01z02", 0, "GENERATE", "V<155,60,440>/V<0,90,0>", 5)
    end
else
    be:MDLsetSeq("SQ_DDMG")
    be:sd("HITLANDMODEL", "hitwall01z02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_lever01z02", 0, "GENERATE", "V<155,60,440>/V<0,90,0>", 5)
end
