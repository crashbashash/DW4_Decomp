if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    if be:FLGisOn(134) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-02", 1)
    end
    if be:FLGisOn(145) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-13", 1)
    end
    if be:FLGisOn(146) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-14", 1)
    end
    if be:FLGisOn(147) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-15", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-02", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-13", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-14", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-15", 1)
