be:MDLsetDMGTurn(0)
if be:MDLgetHp() > 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:MDLaddHp(-100)
    if be:FLGisOn(71) == 0 and be:MDLgetRamNo(be:MDLgetRamNo(), be) == 3 then
        if g_IFLG00 ~= 1 then
            g_IFLG00 = 1
        else
            be:sd("MODELCTRL", "g_dgate02z04", 0, "SQ_SWON")
            be:sd("HITLANDMODEL", "hitdgate02z040", 0, "OFFHIT")
            be:sd("MODELCTRL", "g_upblockz04", 2, "MOVETRANS", "V<80,20,240>/V<0,0,0>")
            be:sd("HITLANDMODEL", "hitupblockz042", 0, "ONHIT")
            be:FLGset(71, 1)
        end
    end
    if be:FLGisOn(72) == 0 and be:MDLgetRamNo(be:MDLgetRamNo(), be) == 2 then
        if g_IFLG01 ~= 1 then
            g_IFLG01 = 1
        else
            be:sd("MODELCTRL", "g_dgate02z04", 1, "SQ_SWON")
            be:sd("HITLANDMODEL", "hitdgate02z041", 0, "OFFHIT")
            be:sd("MODELCTRL", "g_upblockz04", 3, "MOVETRANS", "V<-190,20,-40>/V<0,0,0>")
            be:sd("HITLANDMODEL", "hitupblockz043", 0, "ONHIT")
            be:FLGset(72, 1)
        end
    end
end
