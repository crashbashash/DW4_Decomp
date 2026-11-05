if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    if be:FLGisOn(199) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-13", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-13", 1)
