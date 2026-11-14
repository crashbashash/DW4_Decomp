if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    if be:FLGisOn(121) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-22", 1)
    end
end
