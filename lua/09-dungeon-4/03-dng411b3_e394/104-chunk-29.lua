if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    if be:FLGisOn(135) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-02", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-02", 1)
