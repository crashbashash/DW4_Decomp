if be:MATisAllPlayer() == 1 and be:FLGisOn(107) ~= 1 then
    be:sd("MODELCTRL", "g_d2door", 12, "SQ_SWOF")
    be:sd("HITLANDMODEL", "doorwall13", 0, "ONHIT")
    be:sd("GENERATER", nil, -1, "START", "GENE-08")
    be:MATsetRun(0)
end
