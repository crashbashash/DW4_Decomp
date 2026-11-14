if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    if be:FLGisOn(124) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-05", 1)
    end
end
