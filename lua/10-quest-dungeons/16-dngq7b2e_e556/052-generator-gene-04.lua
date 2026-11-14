if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    if be:FLGisOn(169) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-04", 1)
    end
end
