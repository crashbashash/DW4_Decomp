if be:MATisAllPlayer() == 1 then
    if be:FLGisOn(245) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall06", 0, "ONHIT")
        be:FLGset(245, 1)
    end
    be:MATsetRun(0)
end
