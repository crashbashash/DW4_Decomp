if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    if be:FLGisOn(155) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-12", 1)
    end
end
