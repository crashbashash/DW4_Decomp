if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    if be:FLGisOn(108) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-09", 1)
    elseif be:FLGisOn(109) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-10", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-09", 1)
be:sd("GENERATER", nil, -1, "STOP", "GENE-10", 1)
