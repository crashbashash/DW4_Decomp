if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    if be:FLGisOn(126) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-10", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-10", 1)
