if be:MATisPlayer() == 1 then
    if be:FLGisOn(146) ~= 1 then
        be:sd("MODELCTRL", "g_dbush01", 2, "SQ_FIRE")
        be:sd("GENERATER", nil, -1, "START", "GENE-08")
    end
    be:MATsetRun(0)
end
