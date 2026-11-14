if be:MATisPlayer() == 1 then
    if be:FLGisOn(146) ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 1, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall02", 0, "ONHIT")
        be:sd("GENERATER", nil, -1, "START", "GENE-03")
    else
        be:MATsetRun(0)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-03")
end
