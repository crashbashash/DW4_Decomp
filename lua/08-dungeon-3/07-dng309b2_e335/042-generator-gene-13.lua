if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    if be:FLGisOn(139) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-13", 1)
    end
end
