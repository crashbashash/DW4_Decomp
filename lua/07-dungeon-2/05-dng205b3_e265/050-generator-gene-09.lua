if be:MATisPlayer() == 1 then
    if be:FLGisOn(183) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-09")
    else
        be:MATsetRun(0)
    end
end
