if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    if be:FLGisOn(168) == 1 and be:FLGisOn(148) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-10", 1)
    end
    if be:FLGisOn(169) == 1 and be:FLGisOn(149) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-11", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-10", 1)
    be:sd("GENERATER", nil, -1, "STOP", "GENE-11", 1)
end
