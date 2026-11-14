if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    if be:FLGisOn(161) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-18", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-18", 1)
end
