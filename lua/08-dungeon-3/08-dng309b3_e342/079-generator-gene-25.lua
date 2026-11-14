if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-18")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-23")
    if be:FLGisOn(181) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-25", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-25", 1)
end
