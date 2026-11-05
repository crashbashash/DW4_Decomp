if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    if be:FLGisOn(169) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-07", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-07", 1)
