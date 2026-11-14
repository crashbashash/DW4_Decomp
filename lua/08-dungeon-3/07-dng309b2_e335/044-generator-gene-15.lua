if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    if be:FLGisOn(141) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-15", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-15", 1)
end
