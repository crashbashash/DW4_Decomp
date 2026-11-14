if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    if be:FLGisOn(110) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-11", 1)
    end
end
