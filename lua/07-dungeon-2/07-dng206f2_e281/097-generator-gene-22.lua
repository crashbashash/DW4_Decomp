if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-21")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-24")
    if be:FLGisOn(153) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-22", 1)
    end
end
