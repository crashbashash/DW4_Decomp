if be:MATisPlayer() == 1 then
    if be:FLGisOn(121) ~= 1 then
        if be:FLGisOn(120) == 1 then
            be:sd("GENERATER", nil, -1, "START", "GENE-02")
        end
    else
        be:MATsetRun(0)
    end
end
