if be:MATisPlayer() == 1 then
    if be:FLGisOn(145) ~= 1 then
        be:sd("MODELCTRL", "g_dbush02", 9, "SQ_FIRE")
        be:sd("GENERATER", nil, -1, "START", "GENE-07")
    end
    be:MATsetRun(0)
end
