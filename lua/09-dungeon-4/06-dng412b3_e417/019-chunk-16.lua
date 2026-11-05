if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-22")
    if be:FLGisOn(119) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-20", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-20", 1)
