if be:MATisPlayer() == 1 then
    if be:SYSgetDifficulty() < 2 and be:FLGisOn(108) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-09")
    end
    be:MATsetRun(0)
end
