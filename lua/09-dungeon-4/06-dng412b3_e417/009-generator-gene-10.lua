if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    if be:FLGisOn(109) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-10", 1)
    end
end
