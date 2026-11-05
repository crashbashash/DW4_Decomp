if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    if be:FLGisOn(133) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-06", 1)
    end
    if be:FLGisOn(141) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-14", 1)
    end
    if be:FLGisOn(142) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-15", 1)
    end
    if be:FLGisOn(143) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-16", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-06", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-14", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-15", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-16", 1)
