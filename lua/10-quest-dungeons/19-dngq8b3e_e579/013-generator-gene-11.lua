if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    if be:FLGisOn(197) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-11", 1)
    end
end
