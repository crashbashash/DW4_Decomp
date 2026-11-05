if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    if be:FLGisOn(100) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-01", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-01", 1)
