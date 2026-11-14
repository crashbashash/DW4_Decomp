if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    if be:FLGisOn(108) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-09", 1)
    end
end
