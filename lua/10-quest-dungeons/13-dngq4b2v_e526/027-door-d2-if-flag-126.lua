if be:MATisAllPlayer() == 1 then
    if be:FLGisOn(126) ~= 1 then
        be:sd("MODELCTRL", "g_d2door", 1, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall02", 0, "ONHIT")
        be:sd("GENERATER", nil, -1, "START", "GENE-07")
    else
        be:MATsetRun(0)
    end
end
