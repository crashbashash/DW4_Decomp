if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    if be:FLGisOn(173) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-17", 1)
    end
end
