be:MDLsetDMGTurn(0)
if be:MDLgetHp() > 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:MDLaddHp(-100)
    if be:FLGisOn(46) == 1 then
        be:sd("MODELCTRL", "g_movepass01z02", 0, "SQ_SWON")
        be:sd("HITLANDMODEL", "hitmovepass01z02", 0, "OFFHIT")
        be:FLGset(493, 1)
        be:FLGset(46, 0)
    end
    if be:FLGisOn(47) == 1 then
        be:sd("MODELCTRL", "g_lift02z02", 0, "SQ_SWON")
        be:sd("HITLANDMODEL", "hitlift020", 0, "OFFHIT")
        be:FLGset(47, 0)
    end
    if be:FLGisOn(48) == 1 then
        be:sd("MODELCTRL", "g_movepass02z02", 0, "SQ_SWON")
        be:sd("HITLANDMODEL", "hitmovepass02z02", 0, "OFFHIT")
        be:FLGset(48, 0)
    end
end
