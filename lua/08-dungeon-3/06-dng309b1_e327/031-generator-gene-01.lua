if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    if be:FLGisOn(100) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-01", 1)
    end
end
