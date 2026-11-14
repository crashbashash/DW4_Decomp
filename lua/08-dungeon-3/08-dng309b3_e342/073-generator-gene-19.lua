if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-23")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-25")
    if be:FLGisOn(175) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-19", 1)
    end
end
