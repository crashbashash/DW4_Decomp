if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    if be:FLGisOn(172) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-10", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-10", 1)
