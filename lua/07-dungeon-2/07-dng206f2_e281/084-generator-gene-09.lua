if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-24")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-26")
    if be:FLGisOn(140) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-09", 1)
    end
end
