if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-17")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-21")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-22")
    if be:FLGisOn(150) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-19", 1)
    end
end
