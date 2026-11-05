if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    if be:FLGisOn(105) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-06", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-06", 1)
