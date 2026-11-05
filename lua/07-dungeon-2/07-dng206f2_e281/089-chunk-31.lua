if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-23")
    if be:FLGisOn(145) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-14", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-14", 1)
