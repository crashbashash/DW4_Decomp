if be:MATisPlayer() == 1 then
    if be:FLGisOn(152) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-21")
    else
        be:MATsetRun(0)
    end
end
