if be:MATisAllPlayer() == 1 then
    if be:FLGisOn(178) ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 9, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall10", 0, "ONHIT")
        be:sd("GENERATER", nil, -1, "START", "GENE-16")
    end
    be:MATsetRun(0)
end
