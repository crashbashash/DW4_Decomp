if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-22")
    if be:FLGisOn(169) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-13", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-13", 1)
