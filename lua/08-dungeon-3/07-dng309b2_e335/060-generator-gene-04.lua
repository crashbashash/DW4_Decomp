if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    if be:FLGisOn(130) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-04", 1)
    end
end
