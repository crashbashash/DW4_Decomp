if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-21")
    if be:FLGisOn(152) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-19", 1)
    end
end
