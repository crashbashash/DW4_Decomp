if be:SYSgetDifficulty() == 2 and be:MATisAllPlayer() == 1 and be:FLGisOn(145) + be:FLGisOn(146) + be:FLGisOn(147) + be:FLGisOn(148) < 4 then
    be:sd("MODELCTRL", "g_d2door", 4, "SQ_SWOF")
    be:sd("HITLANDMODEL", "doorwall05", 0, "ONHIT")
end
