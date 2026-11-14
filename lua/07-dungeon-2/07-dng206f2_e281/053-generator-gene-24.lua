if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-22")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-26")
    if be:FLGisOn(155) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-24", 1)
    end
end
