if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    if be:FLGisOn(105) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-06", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-06", 1)
end
