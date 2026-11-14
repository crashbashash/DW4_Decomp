if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    if be:FLGisOn(156) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-13", 1)
    end
end
