if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-22")
    if be:FLGisOn(148) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-17", 1)
    end
end
