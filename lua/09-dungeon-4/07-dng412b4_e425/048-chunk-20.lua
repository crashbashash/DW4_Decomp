if be:MATisPlayer() == 1 then
    if be:FLGisOn(168) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-06")
    else
        be:MATsetRun(0)
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-06")
