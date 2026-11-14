if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-26")
    if be:FLGisOn(178) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-22", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-22", 1)
end
