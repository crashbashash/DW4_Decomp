if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    if be:FLGisOn(132) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-10", 1)
    end
end
