if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    if be:FLGisOn(135) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
    end
    if be:FLGisOn(144) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-17", 1)
    end
    if be:FLGisOn(145) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-18", 1)
    end
    if be:FLGisOn(146) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-19", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-08", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-17", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-18", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-19", 1)
