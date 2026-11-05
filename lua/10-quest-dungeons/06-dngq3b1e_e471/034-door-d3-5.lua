if be:FLGisOn(121) == 1 and be:MATisAllPlayer() == 1 and be:FLGisOn(110) ~= 1 then
    be:sd("MODELCTRL", "g_d3door", 7, "SQ_SWOF")
    be:sd("HITLANDMODEL", "doorwall08", 0, "ONHIT")
    be:FLGset(138, 1)
    be:sd("GENERATER", nil, -1, "START", "GENE-11")
end
be:MATsetRun(0)
