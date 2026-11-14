if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    if be:FLGisOn(107) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
    end
    if be:FLGisOn(112) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-13", 1)
    end
    if be:FLGisOn(113) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-14", 1)
    end
    if be:FLGisOn(114) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-15", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-08", 1)
    be:sd("GENERATER", nil, -1, "STOP", "GENE-13", 1)
    be:sd("GENERATER", nil, -1, "STOP", "GENE-14", 1)
    be:sd("GENERATER", nil, -1, "STOP", "GENE-15", 1)
end
