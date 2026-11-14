if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-21")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-23")
    if be:FLGisOn(117) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-18", 1)
    end
end
