if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    if be:FLGisOn(140) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-02", 1)
    end
end
