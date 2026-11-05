if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    if be:FLGisOn(121) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-05", 1)
    end
    if be:FLGisOn(122) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-06", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-05", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-06", 1)
