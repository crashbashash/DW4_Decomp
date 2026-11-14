if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    if be:FLGisOn(137) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-11", 1)
    end
end
