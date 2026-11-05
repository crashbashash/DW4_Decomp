if be:MATisPlayer() == 1 and be:FLGisOn(116) == 1 and be:FLGisOn(141) ~= 1 then
    be:sd("MODELCTRL", "g_d3door", 6, "SQ_SWOF")
    be:sd("HITLANDMODEL", "doorwall07", 0, "ONHIT")
    be:FLGset(141, 1)
    be:MATsetRun(0)
end
