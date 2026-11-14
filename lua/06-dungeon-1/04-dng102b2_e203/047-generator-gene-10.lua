if be:MATisPlayer() == 1 then
    if be:FLGisOn(124) ~= 1 then
        be:sd("MODELCTRL", "g_dbush01", 3, "SQ_FIRE")
        be:sd("GENERATER", nil, -1, "START", "GENE-10")
    end
    be:MATsetRun(0)
end
