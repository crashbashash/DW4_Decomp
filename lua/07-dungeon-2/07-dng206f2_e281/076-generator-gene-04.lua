if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    if be:FLGisOn(135) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-04", 1)
    end
end
