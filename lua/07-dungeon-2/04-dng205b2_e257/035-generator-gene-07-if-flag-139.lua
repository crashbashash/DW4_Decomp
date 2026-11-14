if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    if be:FLGisOn(139) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-07", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-07", 1)
end
