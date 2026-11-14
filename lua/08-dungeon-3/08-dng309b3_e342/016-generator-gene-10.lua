if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-21")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-22")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-23")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-24")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-25")
    if be:FLGisOn(166) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-10", 1)
    end
end
