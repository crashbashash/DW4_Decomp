if be:MATisAllPlayer() == 1 then
    if be:FLGisOn(158) + be:FLGisOn(159) == 0 then
        be:sd("MODELCTRL", "g_d3door", 1, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall02", 0, "ONHIT")
        be:FLGset(159, 1)
    end
    be:MATsetRun(0)
end
