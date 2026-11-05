if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    if be:FLGisOn(106) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-07", 1)
    end
    if be:FLGisOn(111) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-12", 1)
    end
    if be:FLGisOn(112) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-13", 1)
    end
    if be:FLGisOn(113) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-14", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-07", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-12", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-13", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-14", 1)
