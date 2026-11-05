if be:MATisAllPlayer() == 1 and be:FLGisOn(105) ~= 1 then
    be:sd("MODELCTRL", "g_d2door", 6, "SQ_SWOF")
    be:sd("HITLANDMODEL", "doorwall07", 0, "ONHIT")
    be:sd("GENERATER", nil, -1, "START", "GENE-06")
    be:MATsetRun(0)
end
