if be:MATisPlayer() == 1 then
    if be:FLGisOn(162) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-06")
    end
    be:MATsetRun(0)
end
