if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    if be:FLGisOn(104) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-05", 1)
    end
    if be:FLGisOn(109) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-10", 1)
    end
    if be:FLGisOn(110) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-11", 1)
    end
    if be:FLGisOn(111) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-12", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-05", 1)
    be:sd("GENERATER", nil, -1, "STOP", "GENE-10", 1)
    be:sd("GENERATER", nil, -1, "STOP", "GENE-11", 1)
    be:sd("GENERATER", nil, -1, "STOP", "GENE-12", 1)
end
