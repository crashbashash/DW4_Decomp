if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-22")
    if be:FLGisOn(116) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-17", 1)
    end
end
