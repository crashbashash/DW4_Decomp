if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    if be:FLGisOn(221) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-11", 1)
    end
end
