if be:MATisPlayer() == 1 and be:SYSgetDifficulty() == 2 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    if be:FLGisOn(111) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-12", 1)
    end
end
