if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-23")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-24")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-25")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-26")
    if be:FLGisOn(172) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-16", 1)
    end
end
