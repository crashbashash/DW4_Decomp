if be:MATisAllPlayer() == 1 then
    if be:FLGisOn(246) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 6, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall07", 0, "ONHIT")
        be:FLGset(246, 1)
    end
    be:MATsetRun(0)
end
