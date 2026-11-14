if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    if be:FLGisOn(119) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-06", 1)
    end
end
