if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-19")
    if be:FLGisOn(154) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-21", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-21", 1)
end
