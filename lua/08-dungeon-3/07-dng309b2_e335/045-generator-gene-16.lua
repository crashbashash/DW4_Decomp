if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    if be:FLGisOn(142) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-16", 1)
    end
end
