if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    if be:FLGisOn(145) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-07", 1)
    end
end
