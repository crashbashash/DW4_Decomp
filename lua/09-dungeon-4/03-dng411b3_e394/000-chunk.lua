if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
    if be:FLGisOn(150) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-17", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-17", 1)
