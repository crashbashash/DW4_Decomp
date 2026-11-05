if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    if be:FLGisOn(111) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-12", 1)
    end
    if be:FLGisOn(112) ~= 1 and g_matg12 == 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-13", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-12", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-13", 1)
